/** @file Sensors.h
 * Bosch BME680 simple driver.
 * @author Adrien RICCIARDI
 */
#ifndef H_SENSORS_H
#define H_SENSORS_H

//--------------------------------------------------------------------------------------------------
// Functions
//--------------------------------------------------------------------------------------------------
/** Initialize the SPI module used to communicate with the sensors. */
unsigned char SensorsInitialize(void);

// TEST
signed char a(void);

void SensorsStartMeasurement(void);

#endif
