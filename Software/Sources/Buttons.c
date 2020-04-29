/** @file Buttons.c
 * See Buttons.h for description.
 * @author Adrien RICCIARDI
 */
#include <Buttons.h>

//--------------------------------------------------------------------------------------------------
// Functions
//--------------------------------------------------------------------------------------------------
void ButtonsInitialize(void)
{
	// Set pins as digital
	ANSELBbits.ANSB2 = 0;
	ANSELCbits.ANSC7 = 0;
	ANSELDbits.ANSD4 = 0;
	
	// Make sure pins are configured as inputs
	TRISBbits.TRISB2 = 1;
	TRISCbits.TRISC7 = 1;
	TRISDbits.TRISD4 = 1;
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
