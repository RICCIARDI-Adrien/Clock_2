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

#endif
