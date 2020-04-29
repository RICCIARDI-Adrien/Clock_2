/** @file Buttons.h
 * Manage all board buttons, plus special features for menu-related buttons
 * @author Adrien RICCIARDI
 */
#ifndef H_BUTTONS_H
#define H_BUTTONS_H

#include <xc.h>

//--------------------------------------------------------------------------------------------------
// Constants
//--------------------------------------------------------------------------------------------------
/** The pin the "set" button is connected to. This is an active-low button. */
#define BUTTONS_PIN_SET PORTBbits.RB2
/** The pin the "plus" button is connected to. This is an active-low button. */
#define BUTTONS_PIN_PLUS PORTDbits.RD4
/** The pin the "minus" button is connected to. This is an active-low button. */
#define BUTTONS_PIN_MINUS PORTCbits.RC7

/** The button pin value when it is pressed. */
#define BUTTONS_STATE_PRESSED 0
/** The button pin value when it is released. */
#define BUTTONS_STATE_RELEASED 1

/** Wait for a currently pressed button to be released.
 * @param Button_Pin The pin the button is connected to.
 */
#define BUTTONS_WAIT_FOR_BUTTON_RELEASE(Button_Pin) \
{ \
	while (Button_Pin == BUTTONS_STATE_PRESSED); \
	if (Button_Pin == BUTTONS_STATE_RELEASED) __delay_ms(10); \
}

/** Tell whether the backlight button interrupt fired. */
#define BUTTONS_HAS_INTERRUPT_FIRED() (INTCON3bits.INT1IF)

//--------------------------------------------------------------------------------------------------
// Types
//--------------------------------------------------------------------------------------------------
/** All menu button identifiers. */
typedef enum
{
	BUTTONS_MENU_ID_MINUS,
	BUTTONS_MENU_ID_PLUS,
	BUTTONS_MENU_ID_SET
} TButtonsMenuID;

//--------------------------------------------------------------------------------------------------
// Functions
//--------------------------------------------------------------------------------------------------
/** Initialize the three on-board switches used to navigate into menus. */
void ButtonsInitialize(void);

/** Wait for a menu button to be pressed.
 * @return The pressed button ID.
 */
TButtonsMenuID ButtonsWaitMenuButtonPress(void);

/** Tell whether alarm lever switch is open or closed.
 * @return 0 if alarm is disabled, 1 if alarm is enabled.
 */
unsigned char ButtonsIsAlarmEnabled(void);

/** Must be called when the buttons interrupt fires. */
void ButtonsInterruptHandler(void);

#endif
