/** @file Buttons.c
 * See Buttons.h for description.
 * @author Adrien RICCIARDI
 */
#include <Buttons.h>
#include <Display.h>
#include <Ring.h>

//--------------------------------------------------------------------------------------------------
// Functions
//--------------------------------------------------------------------------------------------------
void ButtonsInitialize(void)
{
	// Set pins as digital
	ANSELB &= 0xF8;
	ANSELCbits.ANSC7 = 0;
	ANSELDbits.ANSD4 = 0;
	
	// Make sure pins are configured as inputs
	TRISB |= 0x07;
	TRISCbits.TRISC7 = 1;
	TRISDbits.TRISD4 = 1;
	
	// Configure backlight button interrupt
	INTCON2bits.INTEDG1 = 0; // Trigger interrupt on falling edge
	INTCON3bits.INT1IP = 0; // Set as low priority
	INTCON3bits.INT1IE = 1; // Enable interrupt
}

TButtonsMenuID ButtonsWaitMenuButtonPress(void)
{
	TButtonsMenuID Pressed_Button;
	
	// Make sure all keys are released
	BUTTONS_WAIT_FOR_BUTTON_RELEASE(BUTTONS_PIN_SET);
	BUTTONS_WAIT_FOR_BUTTON_RELEASE(BUTTONS_PIN_PLUS);
	BUTTONS_WAIT_FOR_BUTTON_RELEASE(BUTTONS_PIN_MINUS);
	
	while (1)
	{
		// Is "set" button pressed ?
		if (BUTTONS_PIN_SET == BUTTONS_STATE_PRESSED)
		{
			Pressed_Button = BUTTONS_MENU_ID_SET;
			break;
		}
		
		// Is "plus" button pressed ?
		if (BUTTONS_PIN_PLUS == BUTTONS_STATE_PRESSED)
		{
			Pressed_Button = BUTTONS_MENU_ID_PLUS;
			break;
		}
		
		// Is "minus" button pressed ?
		if (BUTTONS_PIN_MINUS == BUTTONS_STATE_PRESSED)
		{
			Pressed_Button = BUTTONS_MENU_ID_MINUS;
			break;
		}
		
		// Wait some time to improve buttons debouncing
		__delay_ms(20);
	}
	
	// Add a bit of debouncing
	__delay_ms(10);
	
	return Pressed_Button;
}

void ButtonsInterruptHandler(void)
{
	DisplayTurnBacklightOn();
	RingStop();
	
	// Clear interrupt flag
	INTCON3bits.INT1IF = 0;
}
