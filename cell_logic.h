int SELECT_MAP[MAP_HEIGHT][MAP_WIDTH]={0};
int safeCell_count;							// Indicates how many unopened safe cells are remaining

void mark_flag (int a, int b)	{

	if (SELECT_MAP[a][b] == 0) {
		SELECT_MAP[a][b] = 2;				 // if unrevealed, set to flag
		spritemap[a][b].state = 2;
		drawCell(a,b);
	}
	else if (SELECT_MAP[a][b] == 2) {
		SELECT_MAP[a][b] = 0;				// if flagged, toggle back to unrevealed
		spritemap[a][b].state = 0;
		drawCell(a,b);
	}
}

void cell_reveal(int k, int l) {			 // function to handle cell selection
	int i, j, flagcount=0;
	if (SELECT_MAP[k][l]==0) {
		if (GAME_MAP[k][l] == 9) {			 // if selected cell is a mine
			SELECT_MAP[k][l] = 1;
			spritemap[k][l].state = 1;
			drawCell(k,l);
			game_lost();							 // game over

		}

		else if (GAME_MAP[k][l] == 0)	{	 // if selected cell is an empty cell
			
			map_reveal(k,l);					

		}

		else {
	
			SELECT_MAP[k][l] = 1;		//else, reveals the number of the cell
			safeCell_count--;
			spritemap[k][l].state = 1;
			drawCell(k,l);

		}
	}
	else if (SELECT_MAP[k][l]==1 && GAME_MAP[k][l]!=0) {		// For Chording: if number of adjacent flags matches number of adjacent bombs, open all remaining cells
		for (i=k-1;i<k+2;i++) {									// Count all adjacent flags
			for (j=l-1;j<l+2;j++) {
				if (i==k && j==l) continue;
				if (i<0 || i>=mapHeight[level] || j<0 || j>=mapWidth[level]) continue;
				if (SELECT_MAP[i][j]==2) flagcount++;
			}
		}
		if (flagcount==GAME_MAP[k][l]) {						// If adjacent flag number matches adjacent bomb number
			
			for (i=k-1;i<k+2;i++) {								// Perform cell_reveal() without initiating for game_won();
				for (j=l-1;j<l+2;j++) {
					if (i==k && j==l) continue;
					if (i<0 || i>=mapHeight[level] || j<0 || j>=mapWidth[level]) continue;
					if (SELECT_MAP[i][j]==0) {
						if (GAME_MAP[i][j]==0) map_reveal(i,j);
						else {
							SELECT_MAP[i][j] = 1;
							spritemap[i][j].state = 1;
							drawCell(i,j);
							(GAME_MAP[i][j]==9)? game_lost():safeCell_count--;
						}
						if (safeCell_count==0) break;
					}
				}
			}
		}
	}
	if (safeCell_count==0 && state==GAME) {game_won();}
}

void map_reveal(int n, int m) {								//checks for empty cell and print them

	SELECT_MAP[n][m] = 1;									//updates the current cell as revealed
	safeCell_count--;
	spritemap[n][m].state = 1;
	drawCell(n,m);

	if (m>0 && (SELECT_MAP[n][m-1]==0)) {					//check adjacent cell is not out of bounds, check that adjacent cell is unrevealed
		if ((GAME_MAP[n][m-1] == 0))	{					//check if adjacent cell is	
															//empty and reveal if 
			map_reveal(n,m-1);								//it is not yet revealed
	
		}  
	
		else if (0 < GAME_MAP[n][m-1] < 9) {					//shows cells that are not bombs bounding
																//the empty cells
			SELECT_MAP[n][m-1] = 1;								//updates the current cell as revealed
			safeCell_count--;
			spritemap[n][m-1].state = 1;
			drawCell(n,m-1);
	
		}
	}

	if (m>0 && n<(mapHeight[level]-1) && (SELECT_MAP[n+1][m-1] == 0))	{
		if ((GAME_MAP[n+1][m-1] == 0))	{
					
			map_reveal(n+1,m-1);
	
		}
	
		else if (0 < GAME_MAP[n+1][m-1] < 9) {
	
			SELECT_MAP[n+1][m-1]= 1;
			safeCell_count--;
			spritemap[n+1][m-1].state = 1;
			drawCell(n+1,m-1);
		}
	}

	if (n<(mapHeight[level]-1) && (SELECT_MAP[n+1][m] == 0)) {
		if ((GAME_MAP[n+1][m] == 0))	{		
		
			map_reveal(n+1,m);
	
		}
	
		else if (0 < GAME_MAP[n+1][m] < 9) {
	
			SELECT_MAP[n+1][m]= 1;
			safeCell_count--;
			spritemap[n+1][m].state = 1;
			drawCell(n+1,m);
			
		}
	}
	if (n<(mapHeight[level]-1) && m<(mapWidth[level]-1) && (SELECT_MAP[n+1][m+1] == 0)) {
		if (GAME_MAP[n+1][m+1] == 0)	{
					
			map_reveal(n+1,m+1);
					
		}
	
		else if (0 < GAME_MAP[n+1][m+1] < 9) {
	
			SELECT_MAP[n+1][m+1]= 1;
			safeCell_count--;
			spritemap[n+1][m+1].state = 1;
			drawCell(n+1,m+1);
		}
	}

	if (m<(mapWidth[level]-1) && (SELECT_MAP[n][m+1] == 0)) {
		if (GAME_MAP[n][m+1] == 0)	{
				
			map_reveal(n,m+1);
	
		}
	
		else if (0 < GAME_MAP[n][m+1] < 9) {
	
			SELECT_MAP[n][m+1]= 1;
			safeCell_count--;
			spritemap[n][m+1].state = 1;
			drawCell(n,m+1);
		}
	}

	if (n>0 && m<(mapWidth[level]-1) && (SELECT_MAP[n-1][m+1] == 0)) {
		if ((GAME_MAP[n-1][m+1] == 0))	{
			
			map_reveal(n-1,m+1);
	
		}
	
		else if (0 < GAME_MAP[n-1][m+1] < 9) {
	
			SELECT_MAP[n-1][m+1]= 1;
			safeCell_count--;
			spritemap[n-1][m+1].state = 1;
			drawCell(n-1,m+1);
		}
	}

	if (n>0 && (SELECT_MAP[n-1][m] == 0)) {
		if ((GAME_MAP[n-1][m] == 0))	{
	
			map_reveal(n-1,m);
	
		}
	
		else if (0 < GAME_MAP[n-1][m] < 9) {
	
			SELECT_MAP[n-1][m]= 1;
			safeCell_count--;
			spritemap[n-1][m].state = 1;
			drawCell(n-1,m);
		}
	}

	if (n>0 && m>0 && (SELECT_MAP[n-1][m-1] == 0)) {
		if ((GAME_MAP[n-1][m-1] == 0))	{
	
			map_reveal(n-1,m-1);
	
		}
	
		else if (0 < GAME_MAP[n-1][m-1] < 9) {
	
			SELECT_MAP[n-1][m-1]= 1;
			safeCell_count--;
			spritemap[n-1][m-1].state = 1;
			drawCell(n-1,m-1);
		}
	}

	if (safeCell_count==0) {game_won();}
}		

void level_won()	{
	level++;							// Move to next level
	state = NEXT;						// Set state to prepare next level
	if (level>=2) {						// If already level 2, reset level and timer
		level = 0;
		state = WIN;
		scoreCheck();					// Check if time remaining beats any highscore
		timer = 90;
	}
}

void game_lost(void) {
	state = LOSE;						// Set state to lose, prepare to go back to main menu
	timer=90;
	drawSprite(LOSE1, 113, 120+16, 5);
	drawSprite(LOSE2, 114, 120+32, 5);
}

void game_won (void) {					// Call for level_won()
	drawSprite(WIN1, 113, 120+16, 5);
	drawSprite(WIN2, 114, 120+32, 5);
	level_won();
}
