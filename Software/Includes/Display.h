/** @file Display.h
 * Driver for DEM20485SYH-LY display in 8-bit mode.
 * @author Adrien RICCIARDI
 */
#ifndef H_DISPLAY_H
#define H_DISPLAY_H

#include <xc.h>

//--------------------------------------------------------------------------------------------------
// Constants
//--------------------------------------------------------------------------------------------------
/** Location of the first character of the first line in the display data RAM. */
#define DISPLAY_CURSOR_LOCATION_LINE_1 0
/** Location of the first character of the second line in the display data RAM. */
#define DISPLAY_CURSOR_LOCATION_LINE_2 0x40
/** Location of the first character of the third line in the display data RAM. */
#define DISPLAY_CURSOR_LOCATION_LINE_3 0x14
/** Location of the first character of the fourth line in the display data RAM. */
#define DISPLAY_CURSOR_LOCATION_LINE_4 0x54

/** How many seconds the backlight will remain lighted. */
#define DISPLAY_BACKLIGHT_ON_DELAY 6

/** Tell whether the display timer interrupt fired or not. */
#define DISPLAY_HAS_INTERRUPT_FIRED() (INTCONbits.TMR0IF)

//--------------------------------------------------------------------------------------------------
// Functions
//--------------------------------------------------------------------------------------------------
/** Initialize the display subsystem. */
void DisplayInitialize(void);

/** Write a character at the current cursor location.
 * @param Character The character to display.
 */
void DisplayWriteCharacter(unsigned char Character);

/** Display a zero-terminated string at the current cursor location.
 * @param Pointer_String The string to display.
 */
void DisplayWriteString(char *Pointer_String);

/** Display a decimal signed 16-bit number (with leading minus sign if needed) at the current cursor location.
 * @param Number The number to display.
 */
void DisplayWriteNumber(signed short Number);

/** Set the cursor location.
 * @param Location The new cursor location. Use a constant from DISPLAY_LOCATION_LINE_x and add an offset to it in order to move the cursor to a specific location.
 */
void DisplaySetCursorLocation(unsigned char Location);

/** Clear the whole display an return the cursor to the beginning of the first line. */
void DisplayClear(void);

/** Light the display backlight for DISPLAY_BACKLIGHT_ON_DELAY seconds. */
void DisplayTurnBacklightOn(void);

/** Handle the backlight timer. */
void DisplayInterruptHandler(void);

#endif
