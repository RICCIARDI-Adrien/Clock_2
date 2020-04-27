/** @file Menu_Buttons.c
 * See Menu_Buttons.h for description.
 * @author Adrien RICCIARDI
 */
#include <Menu_Buttons.h>

//--------------------------------------------------------------------------------------------------
// Functions
//--------------------------------------------------------------------------------------------------
void MenuButtonsInitialize(void)
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

TMenuButtonsID MenuButtonsWaitButtonPress(void)
{
	TMenuButtonsID Pressed_Button;
	
	// Make sure all keys are released
	MENU_BUTTONS_WAIT_FOR_BUTTON_RELEASE(MENU_BUTTONS_PIN_SET);
	MENU_BUTTONS_WAIT_FOR_BUTTON_RELEASE(MENU_BUTTONS_PIN_PLUS);
	MENU_BUTTONS_WAIT_FOR_BUTTON_RELEASE(MENU_BUTTONS_PIN_MINUS);
	
	while (1)
	{
		// Is "set" button pressed ?
		if (MENU_BUTTONS_PIN_SET == MENU_BUTTONS_STATE_PRESSED)
		{
			Pressed_Button = MENU_BUTTONS_ID_SET;
			break;
		}
		
		// Is "plus" button pressed ?
		if (MENU_BUTTONS_PIN_PLUS == MENU_BUTTONS_STATE_PRESSED)
		{
			Pressed_Button = MENU_BUTTONS_ID_PLUS;
			break;
		}
		
		// Is "minus" button pressed ?
		if (MENU_BUTTONS_PIN_MINUS == MENU_BUTTONS_STATE_PRESSED)
		{
			Pressed_Button = MENU_BUTTONS_ID_MINUS;
			break;
		}
		
		// Wait some time to improve buttons debouncing
		__delay_ms(20);
	}
	
	// Add a bit of debouncing
	__delay_ms(10);
	
	return Pressed_Button;
}
