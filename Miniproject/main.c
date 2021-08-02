#include "gba.h"

int count=0;
u16 timer=90;
u16 seeded=0;
signed char rank=0;
u8 nameInput[3]={0};

extern int Ncount(int a, int b, int width);				// b+a*width

#include "game_logic.h"
#include "sprites.h"
#include "controls.h"
#include "score.h"
#include "draw.h"
#include "cell_logic.h"
#include "states.h"

void fillPalette(void) {
	int i;

	// Fill the palette in GBA memory
	for (i = 0; i < NCOLS; i++)
		spritePal[i] = palette[i];
}


void fillSprites(void) {
	int i;

	// Load all sprites in GBA memory
	for (i = 0; i < 128*16*16; i++)
		spriteData[i] = (sprites[i*2+1] << 8) + sprites[i*2];

	// draw all sprites on screen, but all of them outside of the screen (starting at position (240,160) the bottom right corner of the GBA screen)
		drawSprite(0, i, 240,160);
}

void Handler(void) {
	REG_IME = 0x00;											// Stop all other interrupt handling, while we handle this current one
	if ((REG_IF & 0x0008) == 0x0008 && state==MENU) {
		count++;											// Used for srand()
	}

	if ((REG_IF & 0x0010) == 0x0010 && state==GAME) {
		timer--;
		drawTimer();
		if (timer==0) {game_lost();}						// End the game if timer reaches 0
	}

	if ((REG_IF & 0x1000) == 0x1000) {
		checkbutton();
	}
    
	REG_IF = REG_IF;                   // Update interrupt table, to confirm we have handled this interrupt
    
	REG_IME = 0x01;                    // Re-enable interrupt handling
}


int main(void) {
	int i;
	// Set Mode 2
	*(unsigned short *) 0x4000000 = 0x40 | 0x2 | 0x1000;
	*(unsigned short *) 0x5000000 = RGB(10,10,10);

	// Fill SpritePal
	fillPalette();

	// Fill SpriteData
	fillSprites();

	scoreInit();

	// Set Handler Function for interrupts and enable selected interrupts
	REG_INT = (int)&Handler;
	REG_TM0D = 65531;
	REG_TM0CNT = TIMER_ENABLE | TIMER_INTERRUPTS | TIMER_FREQUENCY_1024;		// This timer is for seeding the game i.e. srand()
	REG_TM1D = 49148;
	REG_TM1CNT = TIMER_ENABLE | TIMER_INTERRUPTS | TIMER_FREQUENCY_1024;		// This timer is for timing the player
	REG_IE |= 0x1000 | 0x0010 | 0x0008;											// Enable key interrupt
	REG_IME = 0x1;																// Enable interrupt handling
	REG_P1CNT |= 0x4000 | KEY_A | KEY_B | KEY_START | KEY_SELECT | KEY_UP | KEY_DOWN | KEY_LEFT | KEY_RIGHT | KEY_R | KEY_L;
	initialize();
	while(1) {
		if (hold>0) {hold-=17;}													// To introduce delay to button inputs; decrement more to shorten the delay
	}

	return 0;
}

