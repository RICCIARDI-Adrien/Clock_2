/** @file Ring.h
 * Make the buzzer ring and stop.
 * @author Adrien RICCIARDI
 */
#ifndef H_RING_H
#define H_RING_H

#include <xc.h>

//--------------------------------------------------------------------------------------------------
// Constants and macros
//--------------------------------------------------------------------------------------------------
/** Tell if the ring interrupt fired or not. */
#define RING_HAS_INTERRUPT_FIRED() (PIR1bits.TMR1IF)

//--------------------------------------------------------------------------------------------------
// Functions
//--------------------------------------------------------------------------------------------------
/** Initialize the timer used to make the buzzer ring. */
void RingInitialize(void);

/** Make the buzzer ring. */
void RingStart(void);

/** Stop ringing. */
void RingStop(void);

/** Must be called everytime the ring timer interrupt fires. */
void RingInterruptHandler(void);

#endif
