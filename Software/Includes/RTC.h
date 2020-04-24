/** @file RTC.h
 * DS3231M RTC simple driver.
 * @author Adrien RICCIARDI
 */
#ifndef H_RTC_H
#define H_RTC_H

//--------------------------------------------------------------------------------------------------
// Functions
//--------------------------------------------------------------------------------------------------
/** Initialize I2C module used to communicate with RTC chip. */
void RTCInitialize(void);

// TEST
void RTCSetReadAddress(unsigned char Address);
// TEST
unsigned char RTCReadByte(void);

#endif
