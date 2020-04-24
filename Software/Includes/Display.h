/** @file Display.h
 * Driver for DEM20485SYH-LY display in 8-bit mode.
 * @author Adrien RICCIARDI
 */
#ifndef H_DISPLAY_H
#define H_DISPLAY_H

//--------------------------------------------------------------------------------------------------
// Functions
//--------------------------------------------------------------------------------------------------
/** Initialize the display subsystem. */
void DisplayInitialize(void);

/** Write a character at the current cursor location.
 * @parameter Character The character to display.
 */
void DisplayWriteCharacter(unsigned char Character);

/** Set the cursor location.
 * @param Location The new cursor location. Line 1 character locations are in range [0; 0x13], line 2 character locations are in range [0x40; 0x53], line 3 character locations are in range [0x14; 0x27], line 4 character locations are in range [0x54; 0x67].
 */
void DisplaySetCursorLocation(unsigned char Location);

#endif
