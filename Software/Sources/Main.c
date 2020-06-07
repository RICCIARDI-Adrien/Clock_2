/** @file Main.c
 * Clock entry point and main loop.
 * @author Adrien RICCIARDI
 */
#include <Buttons.h>
#include <Display.h>
#include <Ring.h>
#include <RTC.h>
#include <Sensors.h>
#include <string.h>
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

/** Hold the least sampled values since clock power on. */
static TSensorsMeasures Main_Minimum_Measures = // Initialize each value with the biggest impossible value, so any sampled value will be lesser
{
	127,
	32767,
	101
};

/** Hold the last currently sampled values. */
static TSensorsMeasures Main_Current_Measures;

/** Hold the greatest sampled values since clock power on. */
static TSensorsMeasures Main_Maximum_Measures = // Initialize each value with the smallest impossible value, so any sampled value will be greater
{
	-128,
	-32768,
	0
};

//-------------------------------------------------------------------------------------------------
// Private functions
//-------------------------------------------------------------------------------------------------
/** Entry point for all high priority interrupts. */
static void __interrupt(high_priority) MainInterruptHandlerHighPriority(void)
{
	// Play ring melody
	if (RING_HAS_INTERRUPT_FIRED()) RingInterruptHandler();
}

/** Entry point for all low priority interrupts. */
static void __interrupt(low_priority) MainInterruptHandlerLowPriority(void)
{
	// Detect backlight button press
	if (BUTTONS_HAS_INTERRUPT_FIRED()) ButtonsInterruptHandler();

	// Turn display backlight off
	if (DISPLAY_HAS_INTERRUPT_FIRED()) DisplayInterruptHandler();
}

/** Convert a one-byte Binary Coded Decimal number to two ASCII characters.
 * @param BCD_Number The BCD number to convert.
 * @param Pointer_Tens_Character On output, contain the binary value of the number's tens.
 * @param Pointer_Units_Character On output, contain the binary value of the number's units.
 */
static void MainConvertBCDToASCII(unsigned char BCD_Number, unsigned char *Pointer_Tens_Character, unsigned char *Pointer_Units_Character)
{
	*Pointer_Tens_Character = (BCD_Number >> 4) + '0';
	*Pointer_Units_Character = (BCD_Number & 0x0F) + '0';
}

/** Convert a BCD-encoded number into its binary representation.
 * @param BCD_Number The BCD number to convert to binary.
 * @return The corresponding binary number.
 */
static unsigned char MainConvertBCDToBinary(unsigned char BCD_Number)
{
	unsigned char Tens, Units;
	
	// Extract tens and units
	Tens = BCD_Number >> 4;
	Units = BCD_Number & 0x0F;
	
	return (Tens * 10) + Units;
}

/** Allow to select a precise number in a specified interval using the menu buttons.
 * @param Pointer_String_View_Title The view title, displayed on the first display line.
 * @param Pointer_String_Text The text displayed before the number to select.
 * @param Minimum_Value The minimum allowed value (included). When a lower value is requested, the selected number wraps to its maximum value.
 * @param Maximum_Value The maximum allowed value (included). When a higher value is requested, the selected number wraps to its minimum value.
 * @param Current_Value The value to display when entering the view.
 * @return The selected number.
 */
static unsigned short MainShowNumberSelectionView(char *Pointer_String_View_Title, char *Pointer_String_Text, unsigned short Minimum_Value, unsigned short Maximum_Value, unsigned short Current_Value)
{
	unsigned char Text_Length;
	
	// Display strings that won't change
	DisplayClear();
	// Title
	DisplayWriteString(Pointer_String_View_Title);
	// Text
	DisplaySetCursorLocation(DISPLAY_CURSOR_LOCATION_LINE_2);
	DisplayWriteString(Pointer_String_Text);
	// Help
	DisplaySetCursorLocation(DISPLAY_CURSOR_LOCATION_LINE_3 + 1);
	DisplayWriteString("+ et - pour r\001gler");
	DisplaySetCursorLocation(DISPLAY_CURSOR_LOCATION_LINE_4 + 1);
	DisplayWriteString("SET pour continuer");
	
	// Make sure current value is in allowed range
	if ((Current_Value < Minimum_Value) || (Current_Value > Maximum_Value)) Current_Value = Minimum_Value;
	
	// Handle number selection
	Text_Length = strlen(Pointer_String_Text); // Cache text string length
	while (1)
	{
		// Clear number previous trace
		DisplaySetCursorLocation(DISPLAY_CURSOR_LOCATION_LINE_2 + Text_Length);
		DisplayWriteString("     "); // There are up to 5 digits in a 16-bit number
		
		// Display number
		DisplaySetCursorLocation(DISPLAY_CURSOR_LOCATION_LINE_2 + Text_Length);
		DisplayWriteNumber(Current_Value);
		
		// Handle user inputs
		switch (ButtonsWaitMenuButtonPress())
		{
			case BUTTONS_MENU_ID_MINUS:
				if (Current_Value == Minimum_Value) Current_Value = Maximum_Value;
				else Current_Value--;
				break;
			
			// Increase number
			case BUTTONS_MENU_ID_PLUS:
				if (Current_Value >= Maximum_Value) Current_Value = Minimum_Value;
				else Current_Value++;
				break;
				
			case BUTTONS_MENU_ID_SET:
				return Current_Value;
		}
	}
}

/** Default view, displays time, date and sensors measures. */
static inline void MainShowDefaultView(void)
{
	TRTCTime Time, Time_Alarm;
	TRTCDate Date;
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
	DisplaySetCursorLocation(DISPLAY_CURSOR_LOCATION_LINE_2);
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
	
	// Clear temperature field last characters in case the previously displayed string was longer than the current one
	DisplaySetCursorLocation(DISPLAY_CURSOR_LOCATION_LINE_3 + 6);
	DisplayWriteString("  ");
	// Display temperature
	DisplaySetCursorLocation(DISPLAY_CURSOR_LOCATION_LINE_3 + 1);
	DisplayWriteString("T:");
	DisplayWriteNumber(Main_Current_Measures.Temperature);
	DisplayWriteString("\337C");
	
	// Clear pressure field last characters in case the previously displayed string was longer than the current one
	DisplaySetCursorLocation(DISPLAY_CURSOR_LOCATION_LINE_3 + 18);
	DisplayWriteCharacter(' ');
	// Display pressure
	DisplaySetCursorLocation(DISPLAY_CURSOR_LOCATION_LINE_3 + 9);
	DisplayWriteString("P:");
	DisplayWriteNumber(Main_Current_Measures.Pressure);
	DisplayWriteString("mbar");
	
	// Clear humidity field last character in case the previously displayed string was longer than the current one
	DisplaySetCursorLocation(DISPLAY_CURSOR_LOCATION_LINE_4 + 6);
	DisplayWriteString("  ");
	// Display humidity
	DisplaySetCursorLocation(DISPLAY_CURSOR_LOCATION_LINE_4 + 1);
	DisplayWriteString("H:");
	DisplayWriteNumber(Main_Current_Measures.Humidity);
	DisplayWriteCharacter('%');
	
	// Display alarm enabling state
	DisplaySetCursorLocation(DISPLAY_CURSOR_LOCATION_LINE_4 + 9);
	if (ButtonsIsAlarmEnabled()) DisplayWriteString("\002:ON "); // Add an extra space to clear the "OFF" string, which is longer
	else DisplayWriteString("\002:OFF");
	
	// Is it time to ring ?
	RTCGetAlarm(&Time_Alarm);
	if (ButtonsIsAlarmEnabled() && (Time.Hours == Time_Alarm.Hours) && (Time.Minutes == Time_Alarm.Minutes) && (Time.Seconds == 0x00)) RingStart();
}

/** Display a menu allowing to choose which clock parameter to configure. */
static void MainShowConfigurationMenu(void)
{
	unsigned char Selected_Menu_Index = 0;
	TRTCTime Time;
	TRTCDate Date;
	
	while (1)
	{
		// Display menu
		DisplayClear();
		// Set alarm
		if (Selected_Menu_Index == 0) DisplayWriteString("-> ");
		else DisplayWriteString("   ");
		DisplayWriteString("R\001gler alarme");
		// Set time
		DisplaySetCursorLocation(DISPLAY_CURSOR_LOCATION_LINE_2);
		if (Selected_Menu_Index == 1) DisplayWriteString("-> ");
		else DisplayWriteString("   ");
		DisplayWriteString("R\001gler heure");
		// Set date
		DisplaySetCursorLocation(DISPLAY_CURSOR_LOCATION_LINE_3);
		if (Selected_Menu_Index == 2) DisplayWriteString("-> ");
		else DisplayWriteString("   ");
		DisplayWriteString("R\001gler date");
		// Go back
		DisplaySetCursorLocation(DISPLAY_CURSOR_LOCATION_LINE_4);
		if (Selected_Menu_Index == 3) DisplayWriteString("-> ");
		else DisplayWriteString("   ");
		DisplayWriteString("    Retour");
		
		// Handle buttons
		switch (ButtonsWaitMenuButtonPress())
		{
			// Select next menu entry
			case BUTTONS_MENU_ID_MINUS:
				if (Selected_Menu_Index == 3) Selected_Menu_Index = 0; // Loop to menu first entry
				else Selected_Menu_Index++;
				break;
			
			// Select previous menu entry
			case BUTTONS_MENU_ID_PLUS:
				if (Selected_Menu_Index == 0) Selected_Menu_Index = 3; // Loop to menu last entry
				else Selected_Menu_Index--;
				break;
				
			case BUTTONS_MENU_ID_SET:
				// Configure alarm
				if (Selected_Menu_Index == 0)
				{
					// Retrieve current alarm values
					RTCGetAlarm(&Time);
					Time.Hours = MainConvertBCDToBinary(Time.Hours);
					Time.Minutes = MainConvertBCDToBinary(Time.Minutes);
					
					// Configure hour
					Time.Hours = MainShowNumberSelectionView("--- HEURE ALARME ---", " Heure : ", 0, 23, Time.Hours);
					// Configure minutes
					Time.Minutes = MainShowNumberSelectionView("-- MINUTES ALARME --", " Minutes : ", 0, 59, Time.Minutes);
					
					// Configure RTC
					RTCSetAlarm(&Time);
				}
				// Configure time
				else if (Selected_Menu_Index == 1)
				{
					// Retrieve current time values
					RTCGetTime(&Time);
					Time.Hours = MainConvertBCDToBinary(Time.Hours);
					Time.Minutes = MainConvertBCDToBinary(Time.Minutes);
					Time.Seconds = MainConvertBCDToBinary(Time.Seconds);
					
					// Configure hours
					Time.Hours = MainShowNumberSelectionView("--- REGLER HEURE ---", " Heure : ", 0, 23, Time.Hours);
					// Configure minutes
					Time.Minutes = MainShowNumberSelectionView("-- REGLER MINUTES --", " Minutes : ", 0, 59, Time.Minutes);
					// Configure seconds
					Time.Seconds = MainShowNumberSelectionView("- REGLER SECONDES --", " Secondes : ", 0, 59, Time.Seconds);
					
					// Configure RTC
					RTCSetTime(&Time);
				}
				// Configure date
				else if (Selected_Menu_Index == 2)
				{
					// Retrieve current date values
					RTCGetDate(&Date);
					Date.Day = MainConvertBCDToBinary(Date.Day);
					Date.Month = MainConvertBCDToBinary(Date.Month);
					Date.Year = MainConvertBCDToBinary(Date.Year);
					
					// Configure day
					Date.Day = MainShowNumberSelectionView("--- REGLER JOUR ----", " Jour : ", 1, 31, Date.Day);
					// Configure month
					Date.Month = MainShowNumberSelectionView("--- REGLER MOIS ----", " Mois : ", 1, 12, Date.Month);
					// Configure year
					Date.Year = MainShowNumberSelectionView("--- REGLER ANNEE ---", " Ann\001e : 20", 20, 99, Date.Year);
					
					// Configure RTC
					RTCSetDate(&Date);
				}
				// Exit configuration menu
				else if (Selected_Menu_Index == 3)
				{
					DisplayClear();
					return;
				}
				break;
		}
	}
}

/** Show minimum and maximum values of a specific measure.
 * @param Pointer_String_View_Title The measure name. It will be displayed on the first display line.
 * @param Pointer_String_Unit This string will be appended right after a measure value is displayed.
 * @param Minimum_Value Will be displayed after the text "minimum".
 * @param Maximum_Value Will be displayed after the text "maximum".
 */
static void MainShowMeasureValuesView(char *Pointer_String_View_Title, char *Pointer_String_Unit, signed short Minimum_Value, signed short Maximum_Value)
{
	// Display view title
	DisplayClear();
	DisplayWriteString(Pointer_String_View_Title);
	
	// Display minimum value
	DisplaySetCursorLocation(DISPLAY_CURSOR_LOCATION_LINE_2);
	DisplayWriteString("Minimum : ");
	DisplayWriteNumber(Minimum_Value);
	DisplayWriteString(Pointer_String_Unit);
	
	// Display maximum value
	DisplaySetCursorLocation(DISPLAY_CURSOR_LOCATION_LINE_3);
	DisplayWriteString("Maximum : ");
	DisplayWriteNumber(Maximum_Value);
	DisplayWriteString(Pointer_String_Unit);
}

/** Display minimum and maximum values for each measure.
 * @param Is_First_Measure_Shown Set to 0 to start displaying from the last view, set to 1 to start displaying from the first view.
 */
static void MainShowMeasuresView(unsigned char Is_First_Measure_Shown)
{
	typedef enum
	{
		VIEW_ID_TEMPERATURE,
		VIEW_ID_PRESSURE,
		VIEW_ID_HUMIDITY
	} TViewID;
	TViewID Selected_View_ID;
	
	// Determine the first measure to display (i.e. start from beginning or from end of available measures)
	if (Is_First_Measure_Shown) Selected_View_ID = VIEW_ID_TEMPERATURE;
	else Selected_View_ID = VIEW_ID_HUMIDITY;
	
	while (1)
	{
		// Display selected view
		switch (Selected_View_ID)
		{
			// Temperature
			case VIEW_ID_TEMPERATURE:
			{
				MainShowMeasureValuesView("---- TEMPERATURE ---", "\337C", Main_Minimum_Measures.Temperature, Main_Maximum_Measures.Temperature);
				
				// Handle buttons
				switch (ButtonsWaitMenuButtonPress())
				{
					// Return to default view
					case BUTTONS_MENU_ID_MINUS:
					case BUTTONS_MENU_ID_SET:
						return;
					
					// Select pressure view
					case BUTTONS_MENU_ID_PLUS:
						Selected_View_ID = VIEW_ID_PRESSURE;
						break;
				}
				break;
			}
			
			// Pressure
			case VIEW_ID_PRESSURE:
				MainShowMeasureValuesView("----- PRESSION -----", "mbar", Main_Minimum_Measures.Pressure, Main_Maximum_Measures.Pressure);
				
				// Handle buttons
				switch (ButtonsWaitMenuButtonPress())
				{
					// Select temperature view
					case BUTTONS_MENU_ID_MINUS:
						Selected_View_ID = VIEW_ID_TEMPERATURE;
						break;
					
					// Select humidity view
					case BUTTONS_MENU_ID_PLUS:
						Selected_View_ID = VIEW_ID_HUMIDITY;
						break;
						
					// Return to default view
					case BUTTONS_MENU_ID_SET:
						return;
				}
				break;
				
			// Humidity
			case VIEW_ID_HUMIDITY:
				MainShowMeasureValuesView("----- HUMIDITE -----", "%", Main_Minimum_Measures.Humidity, Main_Maximum_Measures.Humidity);
				
				// Handle buttons
				switch (ButtonsWaitMenuButtonPress())
				{
					// Select pressure view
					case BUTTONS_MENU_ID_MINUS:
						Selected_View_ID = VIEW_ID_PRESSURE;
						break;
					
					// Return to default view
					case BUTTONS_MENU_ID_PLUS:
					case BUTTONS_MENU_ID_SET:
						return;
				}
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
		DisplaySetCursorLocation(DISPLAY_CURSOR_LOCATION_LINE_2);
		DisplayWriteString("Please reboot.");
		while (1);
	}
	ButtonsInitialize();
	RingInitialize();
	
	// Enable interrupts
	RCONbits.IPEN = 1; // Enable interrupt priorities
	INTCONbits.GIE = 1; // Enable high priority interrupts
	INTCONbits.PEIE = 1; // Enable low priority interrupts
	
	// Main loop
	while (1)
	{
		// Wait for a new tick to begin
		while ((RTC_TICK_PIN == 0) && (BUTTONS_PIN_SET == BUTTONS_STATE_RELEASED) && (BUTTONS_PIN_PLUS == BUTTONS_STATE_RELEASED) && (BUTTONS_PIN_MINUS == BUTTONS_STATE_RELEASED)); // Stop waiting if a button is pressed
		
		// Sample values once and make them available to all views
		SensorsGetMeasures(&Main_Current_Measures);
		
		// Determine minimum values
		if (Main_Current_Measures.Temperature < Main_Minimum_Measures.Temperature) Main_Minimum_Measures.Temperature = Main_Current_Measures.Temperature;
		if (Main_Current_Measures.Pressure < Main_Minimum_Measures.Pressure) Main_Minimum_Measures.Pressure = Main_Current_Measures.Pressure;
		if (Main_Current_Measures.Humidity < Main_Minimum_Measures.Humidity) Main_Minimum_Measures.Humidity = Main_Current_Measures.Humidity;
		
		// Determine maximum values
		if (Main_Current_Measures.Temperature > Main_Maximum_Measures.Temperature) Main_Maximum_Measures.Temperature = Main_Current_Measures.Temperature;
		if (Main_Current_Measures.Pressure > Main_Maximum_Measures.Pressure) Main_Maximum_Measures.Pressure = Main_Current_Measures.Pressure;
		if (Main_Current_Measures.Humidity > Main_Maximum_Measures.Humidity) Main_Maximum_Measures.Humidity = Main_Current_Measures.Humidity;
		
		// Display configuration menu if "set" button is pressed
		if (BUTTONS_PIN_SET == BUTTONS_STATE_PRESSED)
		{
			MainShowConfigurationMenu();

			// Make sure all keys are released
			BUTTONS_WAIT_FOR_BUTTON_RELEASE(BUTTONS_PIN_SET);
			BUTTONS_WAIT_FOR_BUTTON_RELEASE(BUTTONS_PIN_PLUS);
			BUTTONS_WAIT_FOR_BUTTON_RELEASE(BUTTONS_PIN_MINUS);
		}
		// Display statistics views if "plus" or "minus" buttons are pressed
		else if ((BUTTONS_PIN_MINUS == BUTTONS_STATE_PRESSED) || (BUTTONS_PIN_PLUS == BUTTONS_STATE_PRESSED))
		{
			// Display first or last measures view according to pressed button
			if (BUTTONS_PIN_MINUS == BUTTONS_STATE_PRESSED) MainShowMeasuresView(0);
			else MainShowMeasuresView(1);
			
			// Make sure all keys are released
			BUTTONS_WAIT_FOR_BUTTON_RELEASE(BUTTONS_PIN_SET);
			BUTTONS_WAIT_FOR_BUTTON_RELEASE(BUTTONS_PIN_PLUS);
			BUTTONS_WAIT_FOR_BUTTON_RELEASE(BUTTONS_PIN_MINUS);
			
			// Clean any remaining trace
			DisplayClear();
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
		while ((RTC_TICK_PIN == 1) && (BUTTONS_PIN_SET == BUTTONS_STATE_RELEASED) && (BUTTONS_PIN_PLUS == BUTTONS_STATE_RELEASED) && (BUTTONS_PIN_MINUS == BUTTONS_STATE_RELEASED)); // Stop waiting if a button is pressed
	}
}
