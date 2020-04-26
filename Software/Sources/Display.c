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
	LATCbits.LATC2 = 0;
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
	
	// Clear display
	DisplayWrite(0x01, 0);
	__delay_ms(5); // Wait at least 1.53ms
	
	// Send entry mode set command
	DisplayWrite(0x06, 0); // Enable increment mode, disable entire shift feature
	__delay_ms(1); // Datasheet does not recommends to wait some time, but wait anyway to be sure
}

void DisplayWriteCharacter(unsigned char Character)
{
	DisplayWrite(Character, 1);
}

void DisplayWriteString(unsigned char *Pointer_String)
{
	while (*Pointer_String != 0)
	{
		DisplayWrite(*Pointer_String, 1);
		Pointer_String++;
	}
}

void DisplayWriteNumber(signed short Number)
{
	unsigned char i, Length, String_Number[12]; // One minus sign + 10 digits + terminating zero
	
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
