/** @file Ring.c
 * See Ring.h for description.
 * @author Adrien RICCIARDI
 */
#include <Buttons.h>
#include <Ring.h>
#include <xc.h>

//--------------------------------------------------------------------------------------------------
// Private constants
//--------------------------------------------------------------------------------------------------
/** The pin the buzzer is connected to. */
#define RING_PIN_BUZZER LATCbits.LATC1

//--------------------------------------------------------------------------------------------------
// Private variables
//--------------------------------------------------------------------------------------------------
/** The ring "melody". */
static unsigned char Ring_Tone[] =
{
	1, 1, 1, 1, 1,
	0, 0, 0, 0, 0,
	1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/** The ring "note" index. */
static unsigned char Ring_Tone_Index;

/** How many times the melody will be played before being automatically shut off. */
static unsigned char Ring_Melody_Loops_Count;

//--------------------------------------------------------------------------------------------------
// Public functions
//--------------------------------------------------------------------------------------------------
void RingInitialize(void)
{
	// Configure the buzzer pin as output
	ANSELC &= 0xFD; // Set pin as digital
	RING_PIN_BUZZER = 0; // Make sure buzzer won't ring on boot
	TRISCbits.TRISC1 = 0; // Configure pin as output
	
	// Configure the timer 1 module to trigger an interrupt at 30.5Hz (the lowest frequency that can be reached with this timer clocked by Fosc = 64MHz)
	T1CON = 0x32; // Use Fosc/4 as clock source, enable 1:8 prescaler, enable 16-bit timer mode, do not start timer
	T1GCON = 0; // Disable all gate-related features
	
	// Configure timer 1 interrupt
	IPR1bits.TMR1IP = 1; // Set interrupt as high priority
	PIE1bits.TMR1IE = 1; // Enable interrupt
}

void RingStart(void)
{
	// Start from the first melody note
	RING_PIN_BUZZER = Ring_Tone[0];
	Ring_Tone_Index = 0;
	
	// Melody will be played this amount of time then will be shut down if the user did not 
	Ring_Melody_Loops_Count = 60;
	
	// Clear and start timer
	TMR1H = 0;
	TMR1L = 0;
	T1CONbits.TMR1ON = 1;
}

void RingStop(void)
{
	// Disable the timer
	T1CONbits.TMR1ON = 0;
	
	// Stop ringing
	RING_PIN_BUZZER = 0;
}

void RingInterruptHandler(void)
{
	// Stop the alarm if the alarm button is switched to "disabled", or if the alarm rang too long
	if (!ButtonsIsAlarmEnabled()) RingStop();
	else
	{
		// Make sure timer is cleared
		TMR1H = 0;
		TMR1L = 0;
		
		// Select next tone
		Ring_Tone_Index++;
		if (Ring_Tone_Index >= sizeof(Ring_Tone))
		{
			Ring_Tone_Index = 0;
			Ring_Melody_Loops_Count--; // Restart melody from the beginning
		}
		
		// Play it if all loops have not been played yet
		if (Ring_Melody_Loops_Count == 0) RingStop();
		else RING_PIN_BUZZER = Ring_Tone[Ring_Tone_Index];
	}
	
	// Clear interrupt flag
	PIR1bits.TMR1IF = 0;
}
