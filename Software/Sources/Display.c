/** @file Display.c
 * See Display.h for description.
 * @author Adrien RICCIARDI
 */
#include <Display.h>
#include <stdio.h>
#include <xc.h>

//--------------------------------------------------------------------------------------------------
// Private constants and macros
//--------------------------------------------------------------------------------------------------
/** The R/S signal. */
#define DISPLAY_SIGNAL_RS LATBbits.LATB3
/** The R/W signal. */
#define DISPLAY_SIGNAL_RW LATBbits.LATB4
/** The E signal. */
#define DISPLAY_SIGNAL_E LATBbits.LATB5

//--------------------------------------------------------------------------------------------------
// Private variables
//--------------------------------------------------------------------------------------------------
/** Count how many seconds the backlight is being lighted. */
static unsigned char Display_Backlight_Seconds_Counter; // The timer counts at 1.05Hz

//--------------------------------------------------------------------------------------------------
// Private functions
//--------------------------------------------------------------------------------------------------
/** Write a byte of command or data to the display.
 * @param Byte The byte to write.
 * @param Is_Data Set to 1 of the byte is a data byte, set to 0 if the byte is a command.
 */
inline void DisplayWrite(unsigned char Byte, unsigned char Is_Data)
{
	// Configure control signals
	if (Is_Data) DISPLAY_SIGNAL_RS = 1;
	else DISPLAY_SIGNAL_RS = 0;
	DISPLAY_SIGNAL_RW = 0;
	
	// Set data
	LATA = Byte;
	
	// Execute write cycle
	DISPLAY_SIGNAL_E = 1;
	_delay(8); // Wait 500ns (datasheet requires at least 230ns)
	DISPLAY_SIGNAL_E = 0;
	__delay_us(50); // Write to RAM command needs 43us to complete, so take a bit of margin
}

//--------------------------------------------------------------------------------------------------
// Public functions
//--------------------------------------------------------------------------------------------------
void DisplayInitialize(void)
{
	// Configure pins
	// Display backlight
	ANSELCbits.ANSC2 = 0; // Set pin as digital
	LATCbits.LATC2 = 0; // Make sure it is off on boot
	TRISCbits.TRISC2 = 0;
	// Data port
	ANSELA = 0; // Set all pins as digital
	LATA = 0;
	TRISA = 0;
	// Control signals
	ANSELB &= 0xC7; // Set requested pins as digital
	LATB &= 0xC7;
	TRISB &= 0xC7;
	
	// Wait 30ms as requested by datasheet, and even more to be sure
	__delay_ms(50);
	
	// Send function set command
	DisplayWrite(0x3C, 0); // Set 2-line mode, turn display on
	__delay_ms(1); // Wait at least 39µs
	
	// Send display control command
	DisplayWrite(0x0C, 0); // Turn display on, disable cursor, disable blinking
	__delay_ms(1); // Wait at least 39µs
	
	// Remove any displaying artifact that could remain in display data memory
	DisplayClear();
	
	// Send entry mode set command
	DisplayWrite(0x06, 0); // Enable increment mode, disable entire shift feature
	__delay_ms(1); // Datasheet does not recommend to wait some time, but wait anyway to be sure
	
	// Send special "e acute" character graphics
	DisplayWrite(0x40 | 0x08, 0); // Set CGRAM address to character index 1
	DisplayWrite(0x02, 1);
	DisplayWrite(0x04, 1);
	DisplayWrite(0x0E, 1);
	DisplayWrite(0x11, 1);
	DisplayWrite(0x1F, 1);
	DisplayWrite(0x10, 1);
	DisplayWrite(0x0E, 1);
	DisplayWrite(0x00, 1);
	
	// Send "alarm" character graphics
	DisplayWrite(0x40 | 0x10, 0); // Set CGRAM address to character index 2
	DisplayWrite(0x00, 1);
	DisplayWrite(0x04, 1);
	DisplayWrite(0x0E, 1);
	DisplayWrite(0x0E, 1);
	DisplayWrite(0x0E, 1);
	DisplayWrite(0x1F, 1);
	DisplayWrite(0x00, 1);
	DisplayWrite(0x04, 1);
	
	// Write to DDRAM address, so the next written data will be understood as a character code
	DisplaySetCursorLocation(0);
	
	// Configure timer 0 to generate an interrupt at approximately 1Hz
	T0CON = 0x07; // Do not enable timer, configure it as a 16-bit timer, use Fosc/4 as clock source
	INTCON2bits.TMR0IP = 0; // Set as low priority
	INTCONbits.TMR0IE = 1; // Enable interrupt
}

void DisplayWriteCharacter(unsigned char Character)
{
	DisplayWrite(Character, 1);
}

void DisplayWriteString(char *Pointer_String)
{
	while (*Pointer_String != 0)
	{
		DisplayWrite(*Pointer_String, 1);
		Pointer_String++;
	}
}

void DisplayWriteNumber(signed short Number)
{
	unsigned char i, Length;
	char String_Number[12]; // One minus sign + 10 digits + terminating zero
	
	// Convert number to a displayable string
	Length = sprintf(String_Number, "%d", Number);
	
	// Display it
	for (i = 0; i < Length; i++) DisplayWrite(String_Number[i], 1);
}

void DisplaySetCursorLocation(unsigned char Location)
{
	Location |= 0x80; // Bit 7 is always set for this command
	DisplayWrite(Location, 0);
}

void DisplayClear(void)
{
	DisplayWrite(0x01, 0);
	__delay_ms(2); // Wait at least 1.53ms
}

void DisplayTurnBacklightOn(void)
{
	// Light backlight
	LATCbits.LATC2 = 1;
	
	// Reset seconds counter
	Display_Backlight_Seconds_Counter = DISPLAY_BACKLIGHT_ON_DELAY;
	
	// Restart timer
	// Turn timer off in case it was already running
	T0CONbits.TMR0ON = 0;
	// Clear timer
	TMR0H = 0;
	TMR0L = 0;
	// Start timer
	T0CONbits.TMR0ON = 1;
}

void DisplayInterruptHandler(void)
{
	// Is the required time elapsed ?
	Display_Backlight_Seconds_Counter--;
	if (Display_Backlight_Seconds_Counter == 0)
	{
		// Turn backlight off
		LATCbits.LATC2 = 0;
		
		// Turn timer off
		T0CONbits.TMR0ON = 0;
	}
	
	// Clear interrupt flag
	INTCONbits.TMR0IF = 0;
}
