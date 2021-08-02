void initialize(void) {							// Show main menu
	int i;
	for (i=0 ; i<5 ; i++) {
		drawSprite(TITLE1+i, i, 80+i*16, 40);
	}
	state=MENU;
	level=0;
}

void start_game(void) {							// Called for every level
    int i,j;
	if (!seeded) {								// Seed the game with count if not yet done
		srand(count);
		seeded=1;
	}
	loadMap();									// Reset game arrays
	for (i=0;i<MAP_HEIGHT;i++) {
		for (j=0;j<MAP_WIDTH;j++) {
			SELECT_MAP[i][j]=0;
			GAME_MAP[i][j]=0;
		}
	}
	safeCell_count = mapHeight[level] * mapWidth[level] - totalMines[level];
	create_mines();								// Create map layout
	create_map();
	cursorY = mapHeight[level]/2;				// Place and draw the cursor
	cursorX = mapWidth[level]/2;
	drawSprite(CURSOR, 0, originX[level]+cursorX*10, originY[level]+cursorY*10);
	drawSprite(TIMERLABEL1, 126, 72, 5);		// Draw timer label
	drawSprite(TIMERLABEL2, 127, 72+16, 5);
	//drawSprite(GREYBACKGROUND, 124, 115, 5+16);
	//drawSprite(GREYBACKGROUND, 125, 115+16, 5+16);
	drawTimer();								// Draw timer
	//drawSprite(LEVELLABEL1, 119, 115, 5+16*3);
	//drawSprite(LEVELLABEL2, 120, 115+16, 5+16*3);
	//drawSprite(GREYBACKGROUND, 117, 115, 5+16*4);
	//drawSprite(GREYBACKGROUND, 118, 115+16, 5+16*4);
	//drawSprite(level+19, 116, 115+10, 5+16*4);
	state=GAME;									// Set state to game for player to begin playing
}

void clear_screen(void) {						// Clear all sprites from screen
	int i;
	for (i = 0; i < 128; i++) drawSprite(50, i, 240,160);
}
