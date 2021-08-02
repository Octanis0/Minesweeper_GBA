
#define INPUT                      (KEY_MASK & (~REG_KEYS))
#define SLOW 15
#define FAST 50
#define MENU 0
#define GAME 1
#define LOSE 2
#define WIN 3
#define NEXT 4
#define HIGH 5
#define NEWHIGH 6
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

u16 state=MENU;				// State 0 - Main menu
							// State 1 - Game
							// State 2 - Lose game
							// State 3 - Win game
							// State 4 - Next level
							// State 5 - Highscore screen
							// State 6 = New highscore
int hold=0;

u16 cursorX=4;
u16 cursorY=4;

void buttonA(void) {
	if (state==GAME) {								// When in a level, A reveals a cell
		cell_reveal(cursorY, cursorX);
	}
	if (state==NEWHIGH && cursorX<2) {				// When setting new highscore, A moves to the next letter, or confirms the name if cursor is on third letter
		nextLetter();
	} else if (state==NEWHIGH && cursorX==2) {
		confirmName();
	}
}

void buttonB(void) {								// When in a level, B sets a flag
	if (state==GAME) {
		mark_flag(cursorY,cursorX);
	}
}

void buttonS(void) {
	if (state==HIGH) {										// When in highscore screen, START moves back to main menu
		clear_screen();
		initialize();
	} else if (state==MENU || state==NEXT) {				// When in main menu or waiting for next level, START sets up and begins new/next level
		clear_screen();
		start_game();
	} else if (state==LOSE || (state==WIN && rank==5)) {	// If game is lost or no new highscore is made, START moves back to main menu
		clear_screen();
		initialize();
	} else if (state==WIN && rank<5) {						// If game is won and new highscore is made, START sets up new highscore entry
		clear_screen();
		newScore();
	} else if (state==NEWHIGH && cursorX<2) {				// When setting new highscore, START moves to the next letter, or confirms the name if cursor is on third letter
		nextLetter();
	} else if (state==NEWHIGH && cursorX==2) {
		confirmName();
	}
}

void buttonSel(void) {										// When in main menu, SELECT moves to highscore screen
	if (state==MENU) {
		clear_screen();
		drawScore();
	}
}

void buttonR(void) {
	if (state==GAME) {										// When in a level or setting a new highscore, DPAD-right moves the cursor to the right
		moveCursor(RIGHT);
	}
	if (state==NEWHIGH) {
		nextLetter();
	}
}

void buttonL(void) {
	if (state==GAME) {										// When in a level or setting a new highscore, DPAD-left moves the cursor to the left
		moveCursor(LEFT);
	}
	if (state==NEWHIGH) {
		prevLetter();
	}
}

void buttonU(void) {
	if (state==GAME) {										// When in a level, DPAD-up moves the cursor up
		moveCursor(UP);
	}
	if (state==NEWHIGH) {									// When setting a new highscore, DPAD-up changes the letter in descending order
		scrollLetterUp();
	}
}

void buttonD(void) {
	if (state==GAME) {										// When in a level, DPAD-down moves the cursor down
		moveCursor(DOWN);
	}
	if (state==NEWHIGH) {									// When setting a new highscore, DPAD-down changes the letter in ascending order
		scrollLetterDown();
	}
}

void checkbutton(void) {									// Checks for buttons that are pressed
	u16 buttons = INPUT;
    
	if ((buttons & KEY_A) == KEY_A) {
		if (hold<=0) {										// If hold has been decremented to 0, allow the button press and set hold back to fixed value
			buttonA();										// If hold is not <= 0, button delay is not complete, do not allow button press
			hold = 1000000;
		} /*else {
			hold -= SLOW;
		}*/
	}
	if ((buttons & KEY_B) == KEY_B) {
		if (hold<=0) {
			buttonB();
			hold = 1000000;
		} /*else {
			hold -= SLOW;
		}*/
	}
	if ((buttons & KEY_SELECT) == KEY_SELECT) {
		if (hold<=0) {
			buttonSel();
			hold = 1000000;
		} /*else {
			hold -= SLOW;
		}*/
	}
	if ((buttons & KEY_START) == KEY_START) {
		if (hold<=0) {
			buttonS();
			hold = 1000000;
		} /*else {
			hold -= SLOW;
		}*/
	}
	if ((buttons & KEY_RIGHT) == KEY_RIGHT) {
		if (hold <= 0) {
			buttonR();
			hold = 1000000;
		} /*else if ((INPUT & KEY_R) == KEY_R) {
			hold-=FAST;
		} else {
			hold-=SLOW;
		}*/
	}
	if ((buttons & KEY_LEFT) == KEY_LEFT) {
		if (hold <= 0) {
			buttonL();
			hold = 1000000;
		}/* else if ((INPUT & KEY_R) == KEY_R) {
			hold-=FAST;
		} else {
			hold-=SLOW;
		}*/
	}
	if ((buttons & KEY_UP) == KEY_UP) {
		if (hold <= 0) {
			buttonU();
			hold = 1000000;
		}/* else if ((INPUT & KEY_R) == KEY_R) {
			hold-=FAST;
		} else {
			hold-=SLOW;
		}*/
	}
	if ((buttons & KEY_DOWN) == KEY_DOWN) {
		if (hold <= 0) {
			buttonD();
			hold = 1000000;
		}/* else if ((INPUT & KEY_R) == KEY_R) {
			hold-=FAST;
		} else {
			hold-=SLOW;
		}*/
	}
}

void moveCursor(int action) {										// Moves cursor according to requested action, then redraw the cursor
	switch(action){
	case UP:
		if (cursorY>0) {
			cursorY--;
		}
		break;
	case DOWN:
		if (cursorY<(mapHeight[level]-1)) {
			cursorY++;
		}
		break;
	case LEFT:
		if (cursorX>0) {
			cursorX--;
		}
		break;
	case RIGHT:
		if (cursorX<(mapWidth[level]-1)) {
			cursorX++;
		}
		break;
	}
	drawSprite(CURSOR, 0, originX[level]+cursorX*10, originY[level]+cursorY*10);
}
