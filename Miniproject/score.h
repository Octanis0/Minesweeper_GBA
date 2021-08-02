typedef struct SCORE {
	u8 name[3];
	u8 score;
} SCORE;

SCORE highscore_list[5] = {0};

void scoreInit() {									// Sets an empty highscore table
	int i;
	for (i=0;i<5;i++){
		highscore_list[i].score=99;					// A time of 99 means empty entry
	}
	for (i=0;i<3;i++) {
		nameInput[i]=255;
	}
}

void scoreCheck() {

	signed char shift,i;
	rank = 0;

	while (rank < 5) {
		if (highscore_list[rank].score == 99) {			// if empty entry is found
			highscore_list[rank].score = timer;			// Set the entry
			break;
		}	
		else if (timer > highscore_list[rank].score) {	//if new time is higher than rank time
			for (shift=3;shift>=rank;shift--) {			// Shift all subsequent entries downwards
				highscore_list[shift+1].score = highscore_list[shift].score;
				for (i=0;i<3;i++) highscore_list[shift+1].name[i]=highscore_list[shift].name[i];
			}
			highscore_list[rank].score = timer;			// Set the entry
			break;
			}
		rank ++;										// Rank of 5 means no new highscore, rank of 0-4 means new highscore on that rank
	}
}

void confirmName() {									// Set the name into the highscore table, place NEW sprites to indicate new highscore
	u8 i;
	for (i=0;i<3;i++) {
		highscore_list[rank].name[i]=nameInput[i];
		nameInput[i]=255;
	}
	state=HIGH;											// Set state back to normal highscore screen
	drawSprite(0,34,240,160);
	drawSprite(NEWSCORE1, 34, 13, 30+rank*25);
	drawSprite(NEWSCORE2, 35, 13+16, 30+rank*25);
}
