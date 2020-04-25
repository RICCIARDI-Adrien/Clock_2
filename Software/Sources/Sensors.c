/** @file Sensors.c
 * See Sensors.h for description.
 * @author Adrien RICCIARDI
 */
#include <Sensors.h>
#include <xc.h>

// TEST
#include <Display.h>

//-------------------------------------------------------------------------------------------------
// Private constants and macros
//-------------------------------------------------------------------------------------------------
/** Set chip /SS to low level (hold time must be at least 20ns, so no need to add delay with an instruction clock of 62.5ns). */
#define SENSORS_SELECT_DEVICE() LATCbits.LATC6 = 0

/** Set chip /SS to high level (hold time must be at least 20ns, so no need to add delay with an instruction clock of 62.5ns). */
#define SENSORS_UNSELECT_DEVICE() LATCbits.LATC6 = 1

//-------------------------------------------------------------------------------------------------
// Private functions
//-------------------------------------------------------------------------------------------------
/** Transfer a byte on the SPI bus.
 * @param Byte The byte to transmit.
 * @return The byte received from the device.
 */
static unsigned char SensorsTransferSPIByte(unsigned char Byte)
{
	// Start transfer
	SSP1BUF = Byte;
	
	// Wait for transfer end
	while (!PIR1bits.SSP1IF);
	PIR1bits.SSP1IF = 0; // Reset interrupt flag
	
	// Interrupt flag is set too soon (in the middle of the last clock pulse), so wait a full period (= 1/4MHz) to be sure transmission has finished
	asm("nop\n");
	asm("nop\n");
	asm("nop\n");
	asm("nop\n");
	asm("nop\n"); // Add a little margin
	
	// Get byte received from device
	return SSP1BUF;
}

//--------------------------------------------------------------------------------------------------
// Public functions
//--------------------------------------------------------------------------------------------------
void SensorsInitialize(void)
{
	unsigned char Test;
	
	// Configure pins
	// Set all pins to digital
	ANSELC &= 0x87;
	// Configure pins direction
	TRISCbits.TRISC3 = 0; // SCK pin
	TRISCbits.TRISC4 = 1; // SDI pin
	TRISCbits.TRISC5 = 0; // SDO pin
	SENSORS_UNSELECT_DEVICE();
	TRISCbits.TRISC6 = 0; // /SS pin
	
	// Configure MSSP1 for SPI master operation
	SSP1STAT = 0; // Sample input data at middle of data output time, transmit on transition from idle to active clock state
	SSP1CON1 = 0x31; // Enable SPI module, set SPI clock idle state to high, select SPI master mode with Fosc/16 = 4MHz clock
	
	// Trigger a software reset
	
	
	// TEST display chip ID (which is 97 in decimal)
	SENSORS_SELECT_DEVICE();
	SensorsTransferSPIByte(0x80 | 0x50);
	Test = SensorsTransferSPIByte(0);
	SENSORS_UNSELECT_DEVICE();
	DisplaySetCursorLocation(4);
	DisplayWriteNumber(Test);
}
