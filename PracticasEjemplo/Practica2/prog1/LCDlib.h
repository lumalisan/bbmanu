// Initialize LCD
void LCDInit();

// Clear LCD
void LCDClear();

// Move the cursor of the LCD to home
void LCDMoveHome();
// Move LCD cursor to first line.
void LCDMoveFirstLine();

// Writes a string to the alphanumeric LCD
void LCDPrint(char *str);

// Move LCD cursor left or right
void LCDMoveLeft();
void LCDMoveRight();

// Practica 2
void LCDChangeCursorMode();
void LCDMoveSecondLine();

// Scroll LCD Screen left or right
void LCDScrollLeft();
void LCDScrollRight();

// Hide LCD cursor
void LCDHideCursor();
// Turn on underline LCD cursor
void LCDTurnOnUnderline();
// Turn on blinking-block LCD cursor
void LCDTurnOnBlinking();
