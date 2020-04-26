/** @file Sensors.c
 * See Sensors.h for description.
 * @author Adrien RICCIARDI
 */
#include <bme680.h>
#include <Sensors.h>
#include <xc.h>

//-------------------------------------------------------------------------------------------------
// Private constants and macros
//-------------------------------------------------------------------------------------------------
/** Set chip /SS to low level (hold time must be at least 20ns, so no need to add delay with an instruction clock of 62.5ns). */
#define SENSORS_SELECT_DEVICE() LATCbits.LATC6 = 0

/** Set chip /SS to high level (hold time must be at least 20ns, so no need to add delay with an instruction clock of 62.5ns). */
#define SENSORS_UNSELECT_DEVICE() LATCbits.LATC6 = 1

//-------------------------------------------------------------------------------------------------
// Private variables
//-------------------------------------------------------------------------------------------------
/** The device, made available to all this module functions */
static struct bme680_dev Sensors_BME680_Device;

//-------------------------------------------------------------------------------------------------
// Private functions
//-------------------------------------------------------------------------------------------------
/** Transfer a byte on the SPI bus.
 * @param Byte The byte to transmit.
 * @return The byte received from the device.
 */
static inline unsigned char SensorsTransferSPIByte(unsigned char Byte)
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

/** Callback function called by BME680 library when it needs to wait some milliseconds.
 * @param Period How many milliseconds to wait.
 */
static void BME680DelayMilliseconds(unsigned long Period)
{
	while (Period > 0)
	{
		__delay_ms(1);
		Period--;
	}
}

/** Callback function called by BME680 library to read register values.
 * @param Device_ID Unused here.
 * @param Register_Address The base register targeted by the read command.
 * @param Pointer_Register_Data The data to read from the register and from the ones that follow.
 * @param Data_Bytes_Count How many payload bytes to read.
 * @return Always 0, this function can't fail.
 */
signed char BME680SPIRead(unsigned char __attribute__((unused)) Device_ID, unsigned char Register_Address, unsigned char *Pointer_Register_Data, unsigned short Data_Bytes_Count)
{
	SENSORS_SELECT_DEVICE();
	
	// Send register address
	SensorsTransferSPIByte(Register_Address | 0x80); // Bit 7 must be set to 1 to tell that this is a reading request
	
	// Read all requested bytes
	while (Data_Bytes_Count > 0)
	{
		*Pointer_Register_Data = SensorsTransferSPIByte(0);
		Pointer_Register_Data++;
		Data_Bytes_Count--;
	}
	
	SENSORS_UNSELECT_DEVICE();
	return 0;
}

/** Callback function called by BME680 library to write register values.
 * @param Device_ID Unused here.
 * @param Register_Address The base register targeted by the write command.
 * @param Pointer_Register_Data The data to write to the register and to the ones that follow.
 * @param Data_Bytes_Count How many payload bytes to write.
 * @return Always 0, this function can't fail.
 */
signed char BME680SPIWrite(unsigned char __attribute__((unused)) Device_ID, unsigned char Register_Address, unsigned char *Pointer_Register_Data, unsigned short Data_Bytes_Count)
{
	SENSORS_SELECT_DEVICE();
	
	// Send register address
	SensorsTransferSPIByte(Register_Address & 0x7F); // Bit 7 must be set to 0 to tell that this is a writing request
	
	// Write all requested bytes
	while (Data_Bytes_Count > 0)
	{
		SensorsTransferSPIByte(*Pointer_Register_Data);
		Pointer_Register_Data++;
		Data_Bytes_Count--;
	}
	
	SENSORS_UNSELECT_DEVICE();
	return 0;
}

//--------------------------------------------------------------------------------------------------
// Public functions
//--------------------------------------------------------------------------------------------------
unsigned char SensorsInitialize(void)
{
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
	
	// Probe sensor and load internal calibration settings
	Sensors_BME680_Device.dev_id = 0;
	Sensors_BME680_Device.intf = BME680_SPI_INTF;
	Sensors_BME680_Device.read = BME680SPIRead;
	Sensors_BME680_Device.write = BME680SPIWrite;
	Sensors_BME680_Device.delay_ms = BME680DelayMilliseconds;
	Sensors_BME680_Device.amb_temp = 25;
	if (bme680_init(&Sensors_BME680_Device) != BME680_OK) return 1;
	
	// Configure sensor settings
	// Set humidity oversampling
	Sensors_BME680_Device.tph_sett.os_hum = BME680_OS_2X; // Use 2x oversampling
	// Set pressure oversampling
	Sensors_BME680_Device.tph_sett.os_pres = BME680_OS_4X; // Use 4x oversampling
	// Set temperature oversampling
	Sensors_BME680_Device.tph_sett.os_temp = BME680_OS_2X; // Use 2x oversampling
	// Configure low pass digital filter that is available for temperature and pressure data
	Sensors_BME680_Device.tph_sett.filter = BME680_FILTER_SIZE_3; // Enable IIR filter with a coefficient of 3
	// Disable gas sensor for now
	Sensors_BME680_Device.gas_sett.run_gas = BME680_DISABLE_GAS_MEAS; // Enable it
	
	// Turn sensor on (this must be set before writing the sensor configuration)
	Sensors_BME680_Device.power_mode = BME680_FORCED_MODE;

	// Set the desired sensor configuration
	if (bme680_set_sensor_settings(BME680_OST_SEL | BME680_OSP_SEL | BME680_OSH_SEL | BME680_FILTER_SEL | BME680_GAS_SENSOR_SEL, &Sensors_BME680_Device) != BME680_OK) return 1;

	// Trigger first measure
	SensorsStartMeasurement();
	
	return 0;
}

void SensorsStartMeasurement(void)
{
	bme680_set_sensor_mode(&Sensors_BME680_Device);
}

void SensorsGetMeasures(TSensorsMeasures *Pointer_Measures)
{
	struct bme680_field_data Data;
	
	// Retrieve latest data
	bme680_get_sensor_data(&Data, &Sensors_BME680_Device);
	
	// Convert them to requested scales
	Pointer_Measures->Temperature = Data.temperature / 100; // Convert to Celsius degrees
	Pointer_Measures->Pressure = Data.pressure / 100; // Convert to millibar
	Pointer_Measures->Humidity = Data.humidity / 1000; // Convert to percentage
	// TODO convert air quality
}
