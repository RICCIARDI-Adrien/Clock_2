/** @file Main.c
 * Clock entry point and main loop.
 * @author Adrien RICCIARDI
 */
#include <Display.h>
#include <RTC.h>
#include <Sensors.h>
#include <xc.h>

//-------------------------------------------------------------------------------------------------
// Microcontroller configuration
//-------------------------------------------------------------------------------------------------
// CONFIG1H register
#pragma config FOSC = INTIO67, PLLCFG = ON, PRICLKEN = ON, FCMEN = OFF, IESO = OFF // Use internal oscillator, enable PLL, enable primary clock, disable fail-safe clock monitor, disable oscillator switchover mode
// CONFIG2L register
#pragma config PWRTEN = ON, BOREN = SBORDIS, BORV = 285 // Enable power up timer, enable brown-out reset in hardware only (so it can't be disabled by software), set highest value for brown-out voltage (2.85V)
// CONFIG2H register
#pragma config WDTEN = OFF // Disable watchdog timer
// CONFIG3H register
#pragma config CCP2MX = PORTC1, PBADEN = OFF, CCP3MX = PORTB5, HFOFST = OFF, MCLRE = EXTMCLR // Connect CCP2 module to RC1 pin, port B pin 5..0 are configured as digital I/O on reset, connect CCP3 module to RB5 pin (this CCP module is not used), wait for the oscillator to become stable before starting code execution, enable MCLR pin
// CONFIG4L register
#pragma config STVREN = ON, LVP = OFF, XINST = OFF, DEBUG = OFF // Reset on stack underflow or overflow, disable single supply ICSP, disable extended instruction set, disable background debug
// CONFIG5L register
#pragma config CP0 = OFF, CP1 = OFF // Disable all code protections
// CONFIG5H register
#pragma config CPB = OFF, CPD = OFF // Disable boot block code protection, disable data EEPROM code protection
// CONFIG6L register
#pragma config WRT0 = OFF, WRT1 = OFF // Disable all write protections
// CONFIG6H register
#pragma config WRTC = OFF, WRTB = OFF, WRTD = OFF // Disable configuration registers write protection, disable boot block write protection, disable data EEPROM write protection
// CONFIG7L register
#pragma config EBTR0 = OFF, EBTR1 = OFF // Disable all table read protections
// CONFIG7H register
#pragma config EBTRB = OFF // Disable boot block table read protection

//-------------------------------------------------------------------------------------------------
// Private constants and macros
//-------------------------------------------------------------------------------------------------
/** The pin the "set" button is connected to. This is an active-low button. */
#define MAIN_BUTTON_SET_PIN PORTBbits.RB2
/** The pin the "plus" button is connected to. This is an active-low button. */
#define MAIN_BUTTON_PLUS_PIN PORTCbits.RC7
/** The pin the "minus" button is connected to. This is an active-low button. */
#define MAIN_BUTTON_MINUS_PIN PORTDbits.RD4

/** The button pin value when it is pressed. */
#define MAIN_BUTTON_PRESSED_STATE 0
/** The button pin value when it is released. */
#define MAIN_BUTTON_RELEASED_STATE 1

/** Wait for a currently pressed button to be released.
 * @param Button_Pin The pin the button is connected to.
 */
#define MAIN_WAIT_FOR_BUTTON_RELEASE(Button_Pin) \
{ \
	while (Button_Pin == MAIN_BUTTON_PRESSED_STATE); \
	if (Button_Pin == MAIN_BUTTON_RELEASED_STATE) __delay_ms(10); \
}

//--------------------------------------------------------------------------------------------------
// Private variables
//--------------------------------------------------------------------------------------------------
/** The string corresponding to each day index. */
static char *Pointer_Main_String_Day_Names[] =
{
	"", // Index 0 does not exist
	"Dimanche",
	"Lundi   ",
	"Mardi   ",
	"Mercredi",
	"Jeudi   ",
	"Vendredi",
	"Samedi  "
};

//-------------------------------------------------------------------------------------------------
// Private functions
//-------------------------------------------------------------------------------------------------
/** Initialize the three on-board switches used to configure the clock settings. */
static void MainConfigurationButtonsInitialize(void)
{
	// Set pins as digital
	ANSELBbits.ANSB2 = 0;
	ANSELCbits.ANSC7 = 0;
	ANSELDbits.ANSD4 = 0;
	// Make sure pins are configured as inputs
	TRISBbits.TRISB2 = 1;
	TRISCbits.TRISC7 = 1;
	TRISDbits.TRISD4 = 1;
}

/** Convert a one-byte Binary Coded Decimal number to two ASCII characters.
 * @param BCD_Number The BCD number to convert.
 * @param Pointer_Tens_Character On output, contain the binary value of the number's tens.
 * @param Pointer_Units_Character On output, contain the binary value of the number's units.
 */
static inline void MainConvertBCDToASCII(unsigned char BCD_Number, unsigned char *Pointer_Tens_Character, unsigned char *Pointer_Units_Character)
{
	*Pointer_Tens_Character = (BCD_Number >> 4) + '0';
	*Pointer_Units_Character = (BCD_Number & 0x0F) + '0';
}

/** Default view, displays time, date and sensors measures. */
static inline void MainShowDefaultView(void)
{
	TRTCTime Time;
	TRTCDate Date;
	TSensorsMeasures Measures;
	unsigned char Tens_Character, Units_Character;
	
	// Display time
	RTCGetTime(&Time);
	DisplaySetCursorLocation(6); // Center time on the first line
	// Display hours
	MainConvertBCDToASCII(Time.Hours, &Tens_Character, &Units_Character);
	if (Tens_Character == '0') Tens_Character = ' '; // Do not display the leading zero
	DisplayWriteCharacter(Tens_Character);
	DisplayWriteCharacter(Units_Character);
	DisplayWriteCharacter(':');
	// Display minutes
	MainConvertBCDToASCII(Time.Minutes, &Tens_Character, &Units_Character);
	DisplayWriteCharacter(Tens_Character);
	DisplayWriteCharacter(Units_Character);
	DisplayWriteCharacter(':');
	// Display seconds
	MainConvertBCDToASCII(Time.Seconds, &Tens_Character, &Units_Character);
	DisplayWriteCharacter(Tens_Character);
	DisplayWriteCharacter(Units_Character);
	
	// Display date
	RTCGetDate(&Date);
	DisplaySetCursorLocation(DISPLAY_LOCATION_LINE_2);
	// Display the day name (all names are padded with spaces to be sure to erase a previous name that was longer)
	DisplayWriteString(Pointer_Main_String_Day_Names[Date.Day_Of_Week]);
	DisplayWriteCharacter(' ');
	// Display the day
	MainConvertBCDToASCII(Date.Day, &Tens_Character, &Units_Character);
	DisplayWriteCharacter(Tens_Character);
	DisplayWriteCharacter(Units_Character);
	DisplayWriteCharacter('/');
	// Display the month
	MainConvertBCDToASCII(Date.Month, &Tens_Character, &Units_Character);
	DisplayWriteCharacter(Tens_Character);
	DisplayWriteCharacter(Units_Character);
	DisplayWriteCharacter('/');
	// Display the year
	MainConvertBCDToASCII(Date.Year, &Tens_Character, &Units_Character);
	DisplayWriteCharacter('2');
	DisplayWriteCharacter('0');
	DisplayWriteCharacter(Tens_Character);
	DisplayWriteCharacter(Units_Character);
	
	// Retrieve sensors data
	SensorsGetMeasures(&Measures);
	
	// Clear temperature field last characters in case the previously displayed string was longer than the current one
	DisplaySetCursorLocation(DISPLAY_LOCATION_LINE_3 + 6);
	DisplayWriteString("  ");
	// Display temperature
	DisplaySetCursorLocation(DISPLAY_LOCATION_LINE_3 + 1);
	DisplayWriteString("T:");
	DisplayWriteNumber(Measures.Temperature);
	DisplayWriteCharacter(0xDF); // A japanese character that looks like "degree" sign (DisplayWriteString() was not used because XC8 is not able to recognize \337 sequence)
	DisplayWriteCharacter('C');
	
	// Clear pressure field last characters in case the previously displayed string was longer than the current one
	DisplaySetCursorLocation(DISPLAY_LOCATION_LINE_3 + 18);
	DisplayWriteCharacter(' ');
	// Display pressure
	DisplaySetCursorLocation(DISPLAY_LOCATION_LINE_3 + 9);
	DisplayWriteString("P:");
	DisplayWriteNumber(Measures.Pressure);
	DisplayWriteString("mbar");
	
	// Clear humidity field last character in case the previously displayed string was longer than the current one
	DisplaySetCursorLocation(DISPLAY_LOCATION_LINE_4 + 6);
	DisplayWriteString("  ");
	// Display humidity
	DisplaySetCursorLocation(DISPLAY_LOCATION_LINE_4 + 1);
	DisplayWriteString("H:");
	DisplayWriteNumber(Measures.Humidity);
	DisplayWriteCharacter('%');
	
}

/** Display a menu allowing to choose which clock parameter to configure. */
static void MainShowConfigurationMenu(void)
{
	unsigned char Selected_Menu_Index = 0;
	
	while (1)
	{
		// Display menu
		DisplayClear();
		// Set alarm
		if (Selected_Menu_Index == 0) DisplayWriteString("-> ");
		else DisplayWriteString("   ");
		DisplayWriteString("R\001gler alarme");
		// Set time
		DisplaySetCursorLocation(DISPLAY_LOCATION_LINE_2);
		if (Selected_Menu_Index == 1) DisplayWriteString("-> ");
		else DisplayWriteString("   ");
		DisplayWriteString("R\001gler heure");
		// Set date
		DisplaySetCursorLocation(DISPLAY_LOCATION_LINE_3);
		if (Selected_Menu_Index == 2) DisplayWriteString("-> ");
		else DisplayWriteString("   ");
		DisplayWriteString("R\001gler date");
		// Go back
		DisplaySetCursorLocation(DISPLAY_LOCATION_LINE_4);
		if (Selected_Menu_Index == 3) DisplayWriteString("-> ");
		else DisplayWriteString("   ");
		DisplayWriteString("   Retour");
		
		// Make sure all keys are released
		MAIN_WAIT_FOR_BUTTON_RELEASE(MAIN_BUTTON_SET_PIN);
		MAIN_WAIT_FOR_BUTTON_RELEASE(MAIN_BUTTON_PLUS_PIN);
		MAIN_WAIT_FOR_BUTTON_RELEASE(MAIN_BUTTON_MINUS_PIN);
		
		// TEST
		if (MAIN_BUTTON_SET_PIN == MAIN_BUTTON_PRESSED_STATE)
		{
			DisplayClear();
			break;
		}
	}
}

//-------------------------------------------------------------------------------------------------
// Entry point
//-------------------------------------------------------------------------------------------------
void main(void)
{
	unsigned char Sensors_Measure_Seconds_Counter = 0;
	
	// Set oscillator frequency to 64MHz
	OSCCON = 0x78; // Core enters sleep mode when issuing a SLEEP instruction, select 16MHz frequency for high frequency internal oscillator, device is running from primary clock (set as "internal oscillator" in configuration registers)
	while (!OSCCONbits.HFIOFS); // Wait for the internal oscillator to stabilize
	OSCCON2 = 0x04; // Turn off secondary oscillator, enable primary oscillator drive circuit
	OSCTUNEbits.PLLEN = 1; // Enable 4x PLL
	
	// Initialize modules
	DisplayInitialize();
	RTCInitialize();
	if (SensorsInitialize() != 0)
	{
		DisplayWriteString("BME680 error.");
		DisplaySetCursorLocation(DISPLAY_LOCATION_LINE_2);
		DisplayWriteString("Please reboot.");
		while (1);
	}
	MainConfigurationButtonsInitialize();
	
	while (1)
	{
		// Wait for a new tick to begin
		while ((RTC_TICK_PIN == 0) && (MAIN_BUTTON_SET_PIN == MAIN_BUTTON_RELEASED_STATE)); // Also exit if "set" button is pressed
		
		// Display configuration menu if "set" button is pressed
		if (MAIN_BUTTON_SET_PIN == MAIN_BUTTON_PRESSED_STATE)
		{
			MainShowConfigurationMenu();

			// Make sure all keys are released
			MAIN_WAIT_FOR_BUTTON_RELEASE(MAIN_BUTTON_SET_PIN);
			MAIN_WAIT_FOR_BUTTON_RELEASE(MAIN_BUTTON_PLUS_PIN);
			MAIN_WAIT_FOR_BUTTON_RELEASE(MAIN_BUTTON_MINUS_PIN);
		}
		
		// Always display time and date view, so they are immediately visible when exiting from configuration menu
		MainShowDefaultView();
		
		// Trigger measures each 2 seconds
		Sensors_Measure_Seconds_Counter++;
		if (Sensors_Measure_Seconds_Counter == 2)
		{
			SensorsStartMeasurement();
			Sensors_Measure_Seconds_Counter = 0;
		}
		
		// Wait for tick end
		while ((RTC_TICK_PIN == 1) && (MAIN_BUTTON_SET_PIN == MAIN_BUTTON_RELEASED_STATE)); // Also exit if "set" button is pressed
	}
}
