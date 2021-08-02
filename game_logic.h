#include <stdlib.h>

#define MAP_WIDTH 11
#define MAP_HEIGHT 10


u16 GAME_MAP[MAP_HEIGHT][MAP_WIDTH]={0};
const u16 mapWidth[2] = {6,11};
const u16 mapHeight[2] = {6,10};
const u16 totalMines[2] = {5,12};
const u16 originX[2] = {90,65};
const u16 originY[2] = {42,42};
u16 level = 0;	

void create_mines() {

	int mine_y;											//y coordinate of mine location 
	int mine_x;											//x coordinate of mine location
	int mines = 0;

	while (mines < totalMines[level]) {
		
		mine_y = rand() % mapHeight[level];				//randomly generates y coordinate of a mine 
		mine_x = rand() % mapWidth[level];				//randomly generates x coordinate of a mine

		if (GAME_MAP[mine_y][mine_x] != 9) {			//Check that location does not already have a bomb
			GAME_MAP[mine_y][mine_x] = 9;				//generated mine will be placed in the game map as #9
        	loadCell(mine_y,mine_x,9);					//update spritemap array
			mines++;
		}
	}
}

void mine_count(int x, int y) {

	int count = 0, i, j;

	/*if (GAME_MAP[x][y-1] == 9 && y>0) {		 //check for mine in N direction 
		count++;
	}

	if (GAME_MAP[x+1][y-1] == 9 && x<mapHeight[level]-1 && y>0) {	 //check for mine in NE direction
		count++;
	}

	if (GAME_MAP[x+1][y] == 9 && x<mapHeight[level]-1) {		 //check for mine in E direction 
		count++;
	}

	if (GAME_MAP[x+1][y+1] == 9 && x<mapHeight[level]-1 && y<mapWidth[level]-1) {	 //check fo mine in SE direction
		count++;
	}

	if (GAME_MAP[x][y+1] == 9 && y<mapWidth[level]-1) {		 //check for mine in S direction
		count++;
	}

	if (GAME_MAP[x-1][y+1] == 9 && x>0  && y<mapWidth[level]-1) {	 //check for mine in SW direction
		count++;
	}

	if (GAME_MAP[x-1][y] == 9 && x>0) { 		 //check for mine in W direction 
		count++;
	}

	if (GAME_MAP[x-1][y-1] == 9 && x>0 && y>0) {	 //check for mine in NW direction 
		count++;
	}*/

	for (i=x-1;i<x+2;i++) {							//compressed version of the above comment code
		for (j=y-1;j<y+2;j++) {
			if (x==i && y==j) continue;
			if (i<0 || i>=mapHeight[level] || j<0 || j >=mapWidth[level]) continue;
			if (GAME_MAP[i][j] == 9) count++;
		}
	}

	GAME_MAP[x][y] = count;							//places numbers 0,1,2,3,4,5,6,7,8 into the map 
	loadCell(x,y,count);							//update spritemap array

}

void create_map() {									//fills remaining GAME_MAP with mine count numbers	
	
	int i,j;
	
	for (i=0; i < mapHeight[level]; i++) {

		for(j=0; j < mapWidth[level]; j++) {

			if (GAME_MAP[i][j] != 9) {
				mine_count(i,j);
			}

		}

	}
	
}


/*int main(void) {						//For testing functions only
	int i, j;
	create_mines();
	create_map();
	for (i = 0 ; i<MAP_HEIGHT ; i++) {
		for (j = 0 ; j<MAP_WIDTH ; j++) {
			printf("%d ", GAME_MAP[i][j]);
		}
		printf("\n");
	}
}*/
