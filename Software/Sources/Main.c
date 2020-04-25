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
// Private functions
//-------------------------------------------------------------------------------------------------
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
	unsigned char Tens_Character, Units_Character;
	
	RTCGetTime(&Time);
	
	// Display time
	// Display hours
	MainConvertBCDToASCII(Time.Hours, &Tens_Character, &Units_Character);
	if (Tens_Character == '0') Tens_Character = ' '; // Do not display the leading zero
	DisplaySetCursorLocation(6); // Center time on the first line
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
}

//-------------------------------------------------------------------------------------------------
// Entry point
//-------------------------------------------------------------------------------------------------
void main(void)
{
	unsigned char Byte, Tens_Characters, Units_Characters;
	
	// Set oscillator frequency to 64MHz
	OSCCON = 0x78; // Core enters sleep mode when issuing a SLEEP instruction, select 16MHz frequency for high frequency internal oscillator, device is running from primary clock (set as "internal oscillator" in configuration registers)
	while (!OSCCONbits.HFIOFS); // Wait for the internal oscillator to stabilize
	OSCCON2 = 0x04; // Turn off secondary oscillator, enable primary oscillator drive circuit
	OSCTUNEbits.PLLEN = 1; // Enable 4x PLL
	
	// Initialize modules
	DisplayInitialize();
	RTCInitialize();
	SensorsInitialize();
	
	while (1)
	{
		// Wait for a new tick to begin
		while (RTC_TICK_PIN == 0);
		
		MainShowDefaultView();
		
		// Wait for tick end
		while (RTC_TICK_PIN == 1);
	}
}
