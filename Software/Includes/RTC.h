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
// Types
//--------------------------------------------------------------------------------------------------
/** All date-related data managed by the RTC. All values are in BCD format. */
typedef struct
{
	unsigned char Day_Of_Week; //!< The day of the week in range [1;7]. 1 stands for sunday, 2 for monday and so on.
	unsigned char Day; //!< The day of the month in range [1;31].
	unsigned char Month; //!< The month in range [1;12].
	unsigned char Year; //!< The year in range [0;99].
} TRTCDate;

/** All time-related data managed by the RTC. All values are in BCD format. */
typedef struct
{
	unsigned char Seconds; //!< The seconds in range [0;59].
	unsigned char Minutes; //!< The minutes in range [0;59].
	unsigned char Hours; //!< The hours in range [0;23].
} TRTCTime;

//--------------------------------------------------------------------------------------------------
// Functions
//--------------------------------------------------------------------------------------------------
/** Initialize I2C module used to communicate with RTC chip. */
void RTCInitialize(void);

/** Retrieve current date from RTC.
 * @param Pointer_Date On output, contain the date. Each field is encoded in BCD format.
 */
void RTCGetDate(TRTCDate *Pointer_Date);

/** Configure date in RTC chip registers.
 * @param Pointer_Date Contain the date to set. Each field must be encoded in normal binary, not BCD format.
 * @note Day_Of_Week field value is ignored because it is automatically computed.
 */
void RTCSetDate(TRTCDate *Pointer_Date);

/** Retrieve current time from RTC.
 * @param Pointer_Time On output, contain the time. Each field is encoded in BCD format.
 */
void RTCGetTime(TRTCTime *Pointer_Time);

/** Configure time in RTC chip registers.
 * @param Pointer_Time Contain the time to set. Each field must be encoded in normal binary, not BCD format.
 */
void RTCSetTime(TRTCTime *Pointer_Time);

#endif
