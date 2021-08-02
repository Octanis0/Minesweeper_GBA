typedef struct CELL {
	u16 value;
	u16 state;
} CELL ;

CELL spritemap[MAP_HEIGHT][MAP_WIDTH] = {0};

void drawSprite(int numb, int N, int x, int y) {
	// Same as CA2, make specific sprite (based on its name/numb) appear on screen, as slide number N (each sprite needs a different, arbitrary, N >= 0)
	*(unsigned short *)(0x7000000 + 8*N) = y | 0x2000;
	*(unsigned short *)(0x7000002 + 8*N) = x | 0x4000;
	*(unsigned short *)(0x7000004 + 8*N) = numb*8;
}

void loadMap(void) {								// Resets all CELLs in spritemap array for new game
	int i, j;
	for (i=0; i<MAP_HEIGHT; i++) {
		for (j=0; j<MAP_WIDTH; j++) {
			spritemap[i][j].value=0;
			spritemap[i][j].state=0;
		}
	}
	for (i=0; i<mapHeight[level]; i++) {
		for (j=0; j<mapWidth[level]; j++) {
			drawCell(i,j);
		}
	}
}

void loadCell(int a, int b, int val) {				// Input adjacent bomb number into spritemap from mine_count() in game_logic.h;
	spritemap[a][b].value = val;
}

void drawCell(int a, int b) {						// Gets state and value of requested cell and draws it accordingly
	switch (spritemap[a][b].state) {
		case 0:
			drawSprite(UNOPENED, Ncount(a,b,mapWidth[level])+1, originX[level]+b*10, originY[level]+a*10);
			break;
		case 1:
			drawSprite(spritemap[a][b].value, Ncount(a,b,mapWidth[level])+1, originX[level]+b*10, originY[level]+a*10);
			break;
		case 2:
			drawSprite(FLAG, Ncount(a,b,mapWidth[level])+1, originX[level]+b*10, originY[level]+a*10);
			break;
	}
}

void drawTimer(void) {								// Draws the current timer on the screen
	u8 i,j,k;
	k = timer%10;
	j = timer/10%10;
	i = timer/100%10;
	drawSprite(i+DIGIT_ZERO, 121, 72+2, 5+16);
	drawSprite(j+DIGIT_ZERO, 122, 72+10, 5+16);
	drawSprite(k+DIGIT_ZERO, 123, 72+18, 5+16);
}

void drawScore() {									// Draws the highscore table
	u8 d1, d2;
	u8 i;
	for (i=0;i<4;i++) {
		drawSprite(i+HISCORE1, i, 88+i*16, 10);
	}
	for (i=0;i<5;i++) {
		if (highscore_list[i].score<91) {
			drawSprite(i+DIGIT_ONE, 4+i*6, 50, 30+i*25);
			drawSprite(highscore_list[i].name[0]+LETTER_A, 5+i*6, 86, 30+i*25);
			drawSprite(highscore_list[i].name[1]+LETTER_A, 6+i*6, 86+16, 30+i*25);
			drawSprite(highscore_list[i].name[2]+LETTER_A, 7+i*6, 86+32, 30+i*25);
			d2 = highscore_list[i].score%10;
			d1 = highscore_list[i].score/10%10;
			drawSprite(d1+DIGIT_ZERO, 8+i*6, 170, 30+i*25);
			drawSprite(d2+DIGIT_ZERO, 9+i*6, 170+8, 30+i*25);
		} else {break;}
	}
	state=HIGH;
}

void newScore() {												// Draws highscore table, and clears name of entry to be replaced
	drawScore();
	state=NEWHIGH;
	drawSprite(0, 5+rank*6, 240, 160);
	drawSprite(0, 6+rank*6, 240, 160);
	drawSprite(0, 7+rank*6, 240, 160);
	cursorX=0;
	drawSprite(LETTER_CURSOR, 34, 86+cursorX*16, 33+rank*25);	// Set cursor for name selection
	nameInput[0]=0;
	drawSprite(nameInput[0]+LETTER_A, 5+rank*6, 86, 30+rank*25);
}

void scrollLetterUp() {											// Changes letter (backwards Z to A)
	if (nameInput[cursorX]==0) nameInput[cursorX]=25;
	else nameInput[cursorX]-=1;
	drawSprite(nameInput[cursorX]+LETTER_A, 5+cursorX+rank*6, 86+cursorX*16, 30+rank*25);
}

void scrollLetterDown() {										// Changes letter (forwards from A to Z)
	if (nameInput[cursorX]==25) nameInput[cursorX]=0;
	else nameInput[cursorX]+=1;
	drawSprite(nameInput[cursorX]+LETTER_A, 5+cursorX+rank*6, 86+cursorX*16, 30+rank*25);
}

void nextLetter() {												// Move to next letter
	if (cursorX<2) cursorX++;
	if (nameInput[cursorX]==255) {								// If next letter has not been set, set as A
		nameInput[cursorX]=0;
		drawSprite(nameInput[cursorX]+LETTER_A, 5+cursorX+rank*6, 86+cursorX*16, 30+rank*25);
	}
	drawSprite(LETTER_CURSOR, 34, 86+cursorX*16, 33+rank*25);
}

void prevLetter() {												// Move to previous letter
	if (cursorX>0) cursorX--;
	drawSprite(LETTER_CURSOR, 34, 86+cursorX*16, 33+rank*25);
}

