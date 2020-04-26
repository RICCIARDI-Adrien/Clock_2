/** @file Sensors.c
 * See Sensors.h for description.
 * @author Adrien RICCIARDI
 */
#include <bme680.h>
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

/** Reset register address. */
#define SENSORS_REGISTER_ADDRESS_RESET 0x60 // Page 0
/** Ctrl_hum register address. */
#define SENSORS_REGISTER_ADDRESS_CRTL_HUM 0x72 // Page 1
/** Status register address. */
#define SENSORS_REGISTER_ADDRESS_STATUS 0x73 // Pages 0 and 1
/** Ctrl_meas register address. */
#define SENSORS_REGISTER_ADDRESS_CTRL_MEAS 0x74 // Page 1
/** Config register address. */
#define SENSORS_REGISTER_ADDRESS_CONFIG 0x75 // Page 1
#define SENSORS_REGISTER_ADDRESS_COEFF_ADDR1 0x89 // Page 0

//-------------------------------------------------------------------------------------------------
// Private variables
//-------------------------------------------------------------------------------------------------
/** TODO */
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

static void BME680DelayMilliseconds(unsigned long Period)
{
	while (Period > 0)
	{
		__delay_ms(1);
		Period--;
	}
}

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

/** Read a register content from the chip.
 * @param Register_Address The register address. Use a constant from SENSORS_REGISTER_ADDRESS_xxx.
 * @return The read register value.
 */
static unsigned char SensorsReadRegister(unsigned char Register_Address)
{
	unsigned char Data;
	
	SENSORS_SELECT_DEVICE();
	SensorsTransferSPIByte(Register_Address | 0x80); // Bit 7 must be set to 1 to tell that this is a reading request
	Data = SensorsTransferSPIByte(0);
	SENSORS_UNSELECT_DEVICE();
	
	return Data;
}

/** Write a register content to the chip.
 * @param Register_Address The register address. Use a constant from SENSORS_REGISTER_ADDRESS_xxx.
 * @param Data The register value to write.
 */
static void SensorsWriteRegister(unsigned char Register_Address, unsigned char Data)
{
	SENSORS_SELECT_DEVICE();
	SensorsTransferSPIByte(Register_Address & 0x7F); // Bit 7 must be set to 0 to tell that this is a writing request
	SensorsTransferSPIByte(Data);
	SENSORS_UNSELECT_DEVICE();
}

/** Select the specified register page.
 * @param Registers_Page The page to select (0 or 1). Page 0 addresses registers from 0x80 to 0xFF, page 1 addresses registers from 0 to 0x7F.
 */
static void SensorsSelectRegistersPage(unsigned char Registers_Page)
{
	Registers_Page = (Registers_Page << 4) & 0x10; // Move the page value to the "spi_mem_page" bit
	SensorsWriteRegister(SENSORS_REGISTER_ADDRESS_STATUS, Registers_Page);
}

//--------------------------------------------------------------------------------------------------
// Public functions
//--------------------------------------------------------------------------------------------------
unsigned char SensorsInitialize(void)
{
	//unsigned char Test;
	
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
	
    /* Set the temperature, pressure and humidity settings */
    Sensors_BME680_Device.tph_sett.os_hum = BME680_OS_2X;
    Sensors_BME680_Device.tph_sett.os_pres = BME680_OS_4X;
    Sensors_BME680_Device.tph_sett.os_temp = BME680_OS_2X;
    Sensors_BME680_Device.tph_sett.filter = BME680_FILTER_SIZE_3;

    /* Set the remaining gas sensor settings and link the heating profile */
    Sensors_BME680_Device.gas_sett.run_gas = BME680_ENABLE_GAS_MEAS;
    /* Create a ramp heat waveform in 3 steps */
    Sensors_BME680_Device.gas_sett.heatr_temp = 320; /* degree Celsius */
    Sensors_BME680_Device.gas_sett.heatr_dur = 150; /* milliseconds */

    /* Select the power mode */
    /* Must be set before writing the sensor configuration */
    Sensors_BME680_Device.power_mode = BME680_FORCED_MODE; 

    /* Set the desired sensor configuration */
    if (bme680_set_sensor_settings(BME680_OST_SEL | BME680_OSP_SEL | BME680_OSH_SEL | BME680_FILTER_SEL | BME680_GAS_SENSOR_SEL, &Sensors_BME680_Device) != BME680_OK) return 1;

    /* Set the power mode */
    if (bme680_set_sensor_mode(&Sensors_BME680_Device) != BME680_OK) return 1;
	
	// Trigger a software reset to make sure sensor is in a known state
	/*SensorsSelectRegistersPage(0);
	SensorsWriteRegister(SENSORS_REGISTER_ADDRESS_RESET, 0xB6); 
	__delay_ms(10); // Bosch-provided API waits 10ms for the chip to reboot
	
	// Retrieve temperature calibration data
	
	
	// Configure oversampling for all relevant sensors (datasheet recommends to write them all in a row starting from humidity)
	SENSORS_SELECT_DEVICE();
	SensorsTransferSPIByte(SENSORS_REGISTER_ADDRESS_CRTL_HUM);
	SensorsTransferSPIByte(0x02); // Set a 2x oversampling for humidity sensor
	SensorsTransferSPIByte(SENSORS_REGISTER_ADDRESS_CTRL_MEAS);
	SensorsTransferSPIByte(0x54); // Set a 2x oversampling for temperature sensor, set a 16x oversampling for pressure sensor, do not change chip mode
	SENSORS_UNSELECT_DEVICE();
	
	// Enable IIR filter for temperature and pressure data with a coefficient of 3
	SensorsWriteRegister(SENSORS_REGISTER_ADDRESS_CONFIG, 0x18);
	
	// TODO configure gas sensor
	
	// TEST display chip ID (which is 97 in decimal)
	SENSORS_SELECT_DEVICE();
	SensorsTransferSPIByte(0x80 | 0x50);
	Test = SensorsTransferSPIByte(0);
	SENSORS_UNSELECT_DEVICE();
	DisplaySetCursorLocation(17);
	DisplayWriteNumber(Test);*/
	
	return 0;
}

signed char a(void)
{
	struct bme680_field_data data;
	
	bme680_get_sensor_data(&data, &Sensors_BME680_Device);
	return data.temperature / 100;
}

void SensorsStartMeasurement(void)
{
	bme680_set_sensor_mode(&Sensors_BME680_Device);
}
