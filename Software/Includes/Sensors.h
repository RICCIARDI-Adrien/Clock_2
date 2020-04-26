/** @file Sensors.h
 * Bosch BME680 simple driver.
 * @author Adrien RICCIARDI
 */
#ifndef H_SENSORS_H
#define H_SENSORS_H

//--------------------------------------------------------------------------------------------------
// Types
//--------------------------------------------------------------------------------------------------
/** All measures these sensor can perform. */
typedef struct
{
	signed char Temperature; //!< Temperature in Celsius degrees.
	signed short Pressure; //!< Pressure in millibar.
	signed char Humidity; //!< Humidity in percents.
	unsigned char Air_Quality; //!< Air quality in range [1;7]. 1 is very good, 7 is very bad.
} TSensorsMeasures;

//--------------------------------------------------------------------------------------------------
// Functions
//--------------------------------------------------------------------------------------------------
/** Initialize the SPI module used to communicate with the sensors.
 * @return 0 on success,
 * @return 1 if an error occurred.
 */
unsigned char SensorsInitialize(void);

/** Tell sensors to measure all possible values. */
void SensorsStartMeasurement(void);

/** Retrieve last measured values.
 * @param Pointer_Measures On output, contain the values.
 */
void SensorsGetMeasures(TSensorsMeasures *Pointer_Measures);

#endif
