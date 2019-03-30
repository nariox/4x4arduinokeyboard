#include <HID-Settings.h>
#include <HID-Project.h>

/*  4x4 macro keyboard 
 *  Copyright 2016 by Pedro Nariyoshi <pedro.nariyoshi@gmail.com>
 *  Licensed under GNU General Public License 3.0 or later.
 *  @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>
 *  
 *  Code derived from Button/LED Matrix Scanning Example - 3x3 Keypad
 *  by Jimbo @ SparkFun Electronics
 *    https://learn.sparkfun.com/tutorials/cherry-mx-switch-breakout-hookup-guide
*/

//// Hardware definitions
#define NUM_COLS 4 // Number of switch columns 
#define NUM_ROWS 4 // Number of switch rows

//// Software defined debounce
#define MAX_DEBOUNCE 3

//// Apple keyboard macros
#define KEY_COMMAND KEY_LEFT_GUI
#define KEY_OPTION KEY_LEFT_ALT
#define KEY_EJECT HID_CONSUMER_EJECT

//// Keyboard matrix pin assignments
// Pins connected to rows
static const uint8_t RowPins[NUM_ROWS] = {2,3,4,5};
// Pins connected to columns 
static const uint8_t ColPins[NUM_COLS] = {6,7,8,9};

//// Global variables
// Counter for how long a button has been pressed
static uint8_t debounce_count[NUM_ROWS][NUM_COLS];

void setup()
{
  // Counter to set up pins
  uint8_t i;
  
  // Set row scan pins to output and then to HIGH (not active)
  for (i = 0; i < NUM_ROWS; i++)
  {
    pinMode(RowPins[i], OUTPUT);
    digitalWrite(RowPins[i], HIGH);
  }

  // Set column pins to input with pull-up resistors (no need for external pull-up resistors)
  for (i = 0; i < NUM_COLS; i++)
  {
    pinMode(ColPins[i], INPUT_PULLUP);
  }

  // Initialize USB keyboard
  Keyboard.begin();
  
  // Initialize the debounce counter array
  memset(debounce_count,0,sizeof(debounce_count));
//  for (uint8_t i = 0; i < NUM_COLS; i++)
//  {
//    for (uint8_t j = 0; j < NUM_ROWS; j++)
//    {
//      debounce_count[i][j] = 0;
//    }
//  }
}

void loop() 
{
  // Each run through the scan function operates on a single row
  // of the matrix, kept track of using the currentRow variable.
  static uint8_t currentRow = 0;
  static uint8_t currentCol; // for loop counters

  // Select current row
  digitalWrite(RowPins[currentRow], LOW);

  // Scan through switches on this row:
  for (currentCol = 0; currentCol < NUM_COLS; currentCol++)
  {
    // Read the button. If it's pressed, it should be LOW.
    if (digitalRead(ColPins[currentCol]) == LOW)
    {
      if (debounce_count[currentRow][currentCol] < MAX_DEBOUNCE)
      {
        // Increment a debounce counter
        debounce_count[currentRow][currentCol]++;
        // If debounce counter hits MAX_DEBOUNCE
        // Trigger key press
        if ( debounce_count[currentRow][currentCol] == MAX_DEBOUNCE )
        { 
          pressMacro(currentRow,currentCol); 
        }
      }
    }
    else // Otherwise, button is released
    {
      if ( debounce_count[currentRow][currentCol] > 0)
      { 
        // Decrement debounce counter
        debounce_count[currentRow][currentCol]--;
        if ( debounce_count[currentRow][currentCol] == 0 )
        { // If debounce counter hits 0
          releaseMacro(currentRow,currentCol);
        }
      }
    }
  }

  // Once done scanning, de-select the row pin
  digitalWrite(RowPins[currentRow], HIGH);

  // Increment currentRow, so next time we scan the next row
  currentRow = (currentRow > NUM_ROWS-2) ? 0 : currentRow+1;
//  currentRow++;
//  if (currentRow >= NUM_ROWS)
//  {
//    currentRow = 0;
//  }
}

void pressMacro(uint8_t row, uint8_t col)
{
  switch(row)
  {
    case 0:
      switch(col)
      {
        case 0: // constipated face
          Keyboard.print(">_<");
          break;
        case 1: // Switch between tabs inside adobe programs
          Keyboard.press(KEY_COMMAND);
          Keyboard.press('~');
          break;
        case 2: // Command key
          Keyboard.press(KEY_COMMAND);
          break;
        case 3: // OSX Sleep
          Keyboard.press(KEY_COMMAND);
          Keyboard.press(KEY_OPTION);
          Keyboard.press(KEY_EJECT);
          break;
      }
      break;
    case 1:
      switch(col)
      {
        case 0: // Adobe Illustrator: Lock selected
          Keyboard.press(KEY_COMMAND);
          Keyboard.press(KEY_2);
          break;
        case 1: // Adobe Illustrator: Unlock selected
          Keyboard.press(KEY_COMMAND);
          Keyboard.press(KEY_OPTION);
          Keyboard.press(KEY_2);
          break;
        case 2: // Shift+Tab (to switch to previous app)
          Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.press(KEY_TAB);
          break;
        case 3: // Tab (to switch to next app)
          Keyboard.press(KEY_TAB);
          break;
      }
      break;
    case 2:
          switch(col)
      {
        case 0: // Adobe Photoshop: Decrease brush size
          Keyboard.press('[');
          break;
        case 1: // Adobe Photoshop: Increase brush size
          Keyboard.press(']');
          break;
        case 2: // Adobe Illustrator: Blob brush
          Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.press('b');
          break;
        case 3: // Adobe Illustrator: Merge shape
          Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.press('m');
          break;
      }
      break;
    case 3:
          switch(col)
      {
        case 0: // Undo
          Keyboard.press(KEY_COMMAND);
          Keyboard.press('z');
          break;
        case 1: // Redo
          Keyboard.press(KEY_COMMAND);
          Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.press('z');
          break;
        case 2: // Export
          Keyboard.press(KEY_COMMAND);
          Keyboard.press(KEY_OPTION);
          Keyboard.press('e');
          break;
        case 3: // Save
          Keyboard.press(KEY_COMMAND);
          Keyboard.press('s');
          break;
      }
      break;
  }
}
void releaseMacro(uint8_t row, uint8_t col)
{
  switch(row)
  {
    case 0:
      switch(col)
      {
        case 0:
          break;
        case 1:
          Keyboard.release(KEY_COMMAND);
          Keyboard.release('~');
          break;
        case 2:
          Keyboard.release(KEY_COMMAND);
          break;
        case 3:
          Keyboard.release(KEY_COMMAND);
          Keyboard.release(KEY_OPTION);
          Keyboard.release(KEY_EJECT);
          break;
      }
      break;
    case 1:
      switch(col)
      {
        case 0:
          Keyboard.release(KEY_COMMAND);
          Keyboard.release(KEY_2);
          break;
        case 1:
          Keyboard.release(KEY_COMMAND);
          Keyboard.release(KEY_OPTION);
          Keyboard.release(KEY_2);
          break;
        case 2:
          Keyboard.release(KEY_LEFT_SHIFT);
          Keyboard.release(KEY_TAB);
          break;
        case 3:
          Keyboard.release(KEY_TAB);
          break;
      }
      break;
    case 2:
          switch(col)
      {
        case 0:
          Keyboard.release('[');
          break;
        case 1:
          Keyboard.release(']');
          break;
        case 2:
          Keyboard.release(KEY_LEFT_SHIFT);
          Keyboard.release('b');
          break;
        case 3:
          Keyboard.release(KEY_LEFT_SHIFT);
          Keyboard.release('m');
          break;
      }
      break;
    case 3:
          switch(col)
      {
        case 0:
          Keyboard.release(KEY_COMMAND);
          Keyboard.release('z');
          break;
        case 1:
          Keyboard.release(KEY_COMMAND);
          Keyboard.release(KEY_LEFT_SHIFT);
          Keyboard.release('z');
          break;
        case 2:
          Keyboard.release(KEY_COMMAND);
          Keyboard.release(KEY_OPTION);
          Keyboard.release('e');
          break;
        case 3:
          Keyboard.release(KEY_COMMAND);
          Keyboard.release('s');
          break;
      }
      break;
  }
}
