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
// Private functions
//--------------------------------------------------------------------------------------------------
/** Set the RTC internal address counter to allow reading from that address.
 * @param Address The address to set. Make sure it is valid, or the behaviour will be unpredictable.
 */
static void RTCSetReadAddress(unsigned char Address)
{
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

/** Read as many bytes as requested, starting from the RTC current register address.
 * @param Pointer_Buffer On output, contain the read data. Make sure it is large enough to contain all data.
 * @param Bytes_Count How many consecutive bytes to read from RTC.
 */
static void RTCReadBuffer(unsigned char *Pointer_Buffer, unsigned char Bytes_Count)
{
	unsigned char Byte;
	
	// Send an I2C START
	RTC_I2C_SEND_START();
	RTC_I2C_WAIT_OPERATION_END();
	
	// Send the RTC I2C address
	SSP2BUF = RTC_I2C_ADDRESS | RTC_I2C_ADDRESS_READ_WRITE_BIT_READ;
	RTC_I2C_WAIT_OPERATION_END();
	
	// Read each requested byte
	while (Bytes_Count > 0)
	{
		// Receive the next byte from the device
		SSP2CON2bits.RCEN = 1;
		RTC_I2C_WAIT_OPERATION_END();
		*Pointer_Buffer = SSP2BUF;
		
		// Acknowledge the received byte
		if (Bytes_Count > 1) SSP2CON2bits.ACKDT = 0; // Send an I2C ACK because more bytes must be read
		else SSP2CON2bits.ACKDT = 1; // Send an I2C NACK indicating that no more byte will be read
		SSP2CON2bits.ACKEN = 1;
		RTC_I2C_WAIT_OPERATION_END();
		
		Bytes_Count--;
		Pointer_Buffer++;
	}
		
	// Send an I2C STOP
	RTC_I2C_SEND_STOP();
	RTC_I2C_WAIT_OPERATION_END();
}

/** Write a byte of data to the RTC memory.
 * @param Address The register address.
 * @param Byte The byte to write.
 */
static void RTCWriteByte(unsigned char Address, unsigned char Byte)
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

/** Convert a binary number (in range 0 to 99) to its Binary Coded Decimal representation.
 * @param Number The number to convert. Make sure it is in range [0; 99] or the BCD representation will be wrong.
 * @return The corresponding BCD number.
 */
static unsigned char RTCConvertBinaryToBCD(unsigned char Number)
{
	unsigned char Tens, Units;
	
	// Extract tens
	Tens = Number / 10;
	// Extract units
	Units = Number - (Tens * 10);
	
	return (Tens << 4) | Units;
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

void RTCGetDate(TRTCDate *Pointer_Date)
{
	// Set first date register address
	RTCSetReadAddress(0x03);
	
	// Read all needed registers, the TRTCDate fields are in the same order than the RTC registers
	RTCReadBuffer((unsigned char *) Pointer_Date, 4);
}

void RTCSetDate(TRTCDate *Pointer_Date)
{
	static unsigned char Month_Codes[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	unsigned long Year;
	
	// Determine day of week using Sakamoto's formula
	Year = Pointer_Date->Year + 2000;
	if (Pointer_Date->Month < 3) Year--;
	Pointer_Date->Day_Of_Week = (Year + (Year / 4) - (Year / 100) + (Year / 400) + Month_Codes[Pointer_Date->Month - 1] + Pointer_Date->Day) % 7;
	Pointer_Date->Day_Of_Week++; // Day of week starts from 1 in the RTC chip
	
	// Convert to BCD as RTC handles only BCD numbers (no need to convert day of week value as its value is between 1 and 7)
	Pointer_Date->Day = RTCConvertBinaryToBCD(Pointer_Date->Day);
	Pointer_Date->Month = RTCConvertBinaryToBCD(Pointer_Date->Month);
	Pointer_Date->Year = RTCConvertBinaryToBCD(Pointer_Date->Year);
	
	// Clear "century" flag
	Pointer_Date->Month &= 0x1F;
	
	// Write new date values
	RTCWriteByte(3, Pointer_Date->Day_Of_Week);
	RTCWriteByte(4, Pointer_Date->Day);
	RTCWriteByte(5, Pointer_Date->Month);
	RTCWriteByte(6, Pointer_Date->Year);
}

void RTCGetTime(TRTCTime *Pointer_Time)
{
	// Set first time register address
	RTCSetReadAddress(0);
	
	// Read all needed registers, the TRTCTime fields are in the same order than the RTC registers
	RTCReadBuffer((unsigned char *) Pointer_Time, 3);
	
	// Discard control bits from hour value
	Pointer_Time->Hours &= 0x3F;
}

void RTCSetTime(TRTCTime *Pointer_Time)
{
	// Convert all fields to BCD (RTC expects BCD)
	Pointer_Time->Hours = RTCConvertBinaryToBCD(Pointer_Time->Hours);
	Pointer_Time->Minutes = RTCConvertBinaryToBCD(Pointer_Time->Minutes);
	Pointer_Time->Seconds = RTCConvertBinaryToBCD(Pointer_Time->Seconds);
	
	// Configure hours to be in 24-hour format
	Pointer_Time->Hours &= 0x3F;
	
	// Set time starting by seconds, so counting mechanism is blocked for 1 second to let the time to write all needed registers (see datasheet for more information)
	RTCWriteByte(0, Pointer_Time->Seconds);
	RTCWriteByte(1, Pointer_Time->Minutes);
	RTCWriteByte(2, Pointer_Time->Hours);
}

void RTCGetAlarm(TRTCTime *Pointer_Alarm_Time)
{
	// Set "alarm 1 minutes" register address
	RTCSetReadAddress(8);
	
	// Read minutes then hour, seconds are ignored
	RTCReadBuffer(&Pointer_Alarm_Time->Minutes, 2);
	
	// Maker sure some control bits are not set
	Pointer_Alarm_Time->Minutes &= 0x7F;
	Pointer_Alarm_Time->Hours &= 0x1F;
}

void RTCSetAlarm(TRTCTime *Pointer_Alarm_Time)
{
	// Convert all relevant fields to BCD
	Pointer_Alarm_Time->Hours = RTCConvertBinaryToBCD(Pointer_Alarm_Time->Hours);
	Pointer_Alarm_Time->Minutes = RTCConvertBinaryToBCD(Pointer_Alarm_Time->Minutes);
	
	// Write them to alarm 1 registers
	RTCWriteByte(8, Pointer_Alarm_Time->Minutes);
	RTCWriteByte(9, Pointer_Alarm_Time->Hours);
}
