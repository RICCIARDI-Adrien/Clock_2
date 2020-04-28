/** @file Menu_Buttons.h
 * Manage "set", "plus" and "minus" buttons.
 * @author Adrien RICCIARDI
 */
#ifndef H_MENU_BUTTONS_H
#define H_MENU_BUTTONS_H

#include <xc.h>

//--------------------------------------------------------------------------------------------------
// Constants
//--------------------------------------------------------------------------------------------------
/** The pin the "set" button is connected to. This is an active-low button. */
#define MENU_BUTTONS_PIN_SET PORTBbits.RB2
/** The pin the "plus" button is connected to. This is an active-low button. */
#define MENU_BUTTONS_PIN_PLUS PORTDbits.RD4
/** The pin the "minus" button is connected to. This is an active-low button. */
#define MENU_BUTTONS_PIN_MINUS PORTCbits.RC7

/** The button pin value when it is pressed. */
#define MENU_BUTTONS_STATE_PRESSED 0
/** The button pin value when it is released. */
#define MENU_BUTTONS_STATE_RELEASED 1

/** Wait for a currently pressed button to be released.
 * @param Button_Pin The pin the button is connected to.
 */
#define MENU_BUTTONS_WAIT_FOR_BUTTON_RELEASE(Button_Pin) \
{ \
	while (Button_Pin == MENU_BUTTONS_STATE_PRESSED); \
	if (Button_Pin == MENU_BUTTONS_STATE_RELEASED) __delay_ms(10); \
}

//--------------------------------------------------------------------------------------------------
// Types
//--------------------------------------------------------------------------------------------------
/** All menu button identifiers. */
typedef enum
{
	MENU_BUTTONS_ID_MINUS,
	MENU_BUTTONS_ID_PLUS,
	MENU_BUTTONS_ID_SET
} TMenuButtonsID;

//--------------------------------------------------------------------------------------------------
// Functions
//--------------------------------------------------------------------------------------------------
/** Initialize the three on-board switches used to navigate into menus. */
void MenuButtonsInitialize(void);

/** Wait for a button to be pressed.
 * @return The pressed button ID.
 */
TMenuButtonsID MenuButtonsWaitButtonPress(void);

#endif
