/** @file RTC.c
 * See RTC.h for description.
 * @author Adrien RICCIARDI
 */
#include <RTC.h>
#include <xc.h>

//--------------------------------------------------------------------------------------------------
// Private constants and macros
//--------------------------------------------------------------------------------------------------
/** The RTC I2C address ready to be sent on the bus (i.e. shifted by one on the left). The R/#W bit must be OR'ed if needed. */
#define RTC_I2C_ADDRESS 0xD0

/** The R/#W bit Read value in the I2C protocol. */
#define RTC_I2C_ADDRESS_READ_WRITE_BIT_READ 1
/** The R/#W bit Write value in the I2C protocol. */
#define RTC_I2C_ADDRESS_READ_WRITE_BIT_WRITE 0

/** Send a Start condition over the I2C bus. */
#define RTC_I2C_SEND_START() \
{ \
	PIR3bits.SSP2IF = 0; \
	SSP2CON2bits.SEN = 1; \
}

/** Send a Stop condition over the I2C bus. */
#define RTC_I2C_SEND_STOP() SSP2CON2bits.PEN = 1

/** Wait until the previous I2C operation has finished. */
#define RTC_I2C_WAIT_OPERATION_END() \
{ \
	while (!PIR3bits.SSP2IF); \
	PIR3bits.SSP2IF = 0; \
}

//--------------------------------------------------------------------------------------------------
// Public functions
//--------------------------------------------------------------------------------------------------
void RTCInitialize(void)
{
	// Configure pins as inputs
	ANSELD &= 0xF8; // Set pins as digital
	TRISD |= 0x07;
	
	// Initialize the I2C module at 100KHz
	SSP2ADD = 159; // Set a 100KHz clock with a 64MHz system clock
	SSP2STAT = 0x80; // Disable slew rate control as required for 100KHz speed mode, disable SMbus levels detection
	SSP2CON2 = 0; // Reset communication flags
	SSP2CON3 = 0; // Disable interrupts generation on specific I2C events
	SSP2CON1 = 0x38; // Enable I2C module, enable I2C clock generation, set I2C master mode
	
	// Enable 1Hz signal generation
	RTCWriteByte(0x0E, 0x18); // Set default boot values and enable 1Hz square-wave
}

void RTCSetReadAddress(unsigned char Address)
{
	// Do nothing if the address is bad
	//if (Address >= RTC_MEMORY_SIZE) return;
	
	// Set the byte address to read doing a fake write
	// Send an I2C START
	RTC_I2C_SEND_START();
	RTC_I2C_WAIT_OPERATION_END();
	
	// Send the RTC I2C address
	SSP2BUF= RTC_I2C_ADDRESS | RTC_I2C_ADDRESS_READ_WRITE_BIT_WRITE;
	RTC_I2C_WAIT_OPERATION_END();
	
	// Send the byte address
	SSP2BUF = Address;
	RTC_I2C_WAIT_OPERATION_END();
	
	// Send an I2C STOP
	RTC_I2C_SEND_STOP();
	RTC_I2C_WAIT_OPERATION_END();
}

unsigned char RTCReadByte(void)
{
	unsigned char Byte;
	
	// Send an I2C START
	RTC_I2C_SEND_START();
	RTC_I2C_WAIT_OPERATION_END();
	
	// Send the RTC I2C address
	SSP2BUF = RTC_I2C_ADDRESS | RTC_I2C_ADDRESS_READ_WRITE_BIT_READ;
	RTC_I2C_WAIT_OPERATION_END();
	
	// Receive the byte from the device
	SSP2CON2bits.RCEN = 1;
	RTC_I2C_WAIT_OPERATION_END();
	Byte = SSP2BUF;
	
	// Send an I2C NACK to the device
	SSP2CON2bits.ACKDT = 1; // Send an I2C NACK indicating that no more byte will be read
	SSP2CON2bits.ACKEN = 1;
	RTC_I2C_WAIT_OPERATION_END();
	
	// Send an I2C STOP
	RTC_I2C_SEND_STOP();
	RTC_I2C_WAIT_OPERATION_END();
	
	return Byte;
}

void RTCWriteByte(unsigned char Address, unsigned char Byte)
{
	// Send an I2C START
	RTC_I2C_SEND_START();
	RTC_I2C_WAIT_OPERATION_END();
	
	// Send the RTC I2C address
	SSP2BUF = RTC_I2C_ADDRESS | RTC_I2C_ADDRESS_READ_WRITE_BIT_WRITE;
	RTC_I2C_WAIT_OPERATION_END();
	
	// Send the byte address
	SSP2BUF = Address;
	RTC_I2C_WAIT_OPERATION_END();
	
	// Send the byte value
	SSP2BUF = Byte;
	RTC_I2C_WAIT_OPERATION_END();
	
	// Send an I2C STOP
	RTC_I2C_SEND_STOP();
	RTC_I2C_WAIT_OPERATION_END();
	
	// The minimum bus free time between a STOP and a START must be at least 1.3µs
	__delay_us(3);
}
