/** @file RTC.h
 * DS3231M RTC simple driver.
 * @author Adrien RICCIARDI
 */
#ifndef H_RTC_H
#define H_RTC_H

#include <xc.h>

//--------------------------------------------------------------------------------------------------
// Constants
//--------------------------------------------------------------------------------------------------
/** The RTC 1Hz signal pin state. */
#define RTC_TICK_PIN PORTDbits.RD2

//--------------------------------------------------------------------------------------------------
// Functions
//--------------------------------------------------------------------------------------------------
/** Initialize I2C module used to communicate with RTC chip. */
void RTCInitialize(void);

// TEST
void RTCSetReadAddress(unsigned char Address);
// TEST
unsigned char RTCReadByte(void);

/** Write a byte of data to the RTC memory.
 * @param Address The register address.
 * @param Byte The byte to write.
 */
void RTCWriteByte(unsigned char Address, unsigned char Byte);

#endif
