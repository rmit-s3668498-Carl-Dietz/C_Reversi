#include "gameboard.h"

/*This function initialises the board, setting all cells to blank then setting starting locations*/

void initBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH])
{
	int x = 0;
	int y = 0;

	for(x=0; x<BOARD_WIDTH;x++)
	{
		for(y=0;y<BOARD_HEIGHT;y++)
		{
			board[x][y] = BLANK;
			
		}
		y = 0;
	}
	
	board[START_CELL][HALF_HEIGHT] = CYAN;
	board[HALF_WIDTH][START_CELL] = CYAN;
	board[START_CELL][START_CELL] = RED;
	board[HALF_WIDTH][HALF_HEIGHT] = RED;
}

/*This function draws the board in the console*/

void displayBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Player * first, Player * second)
{
	int a = BOARD_ARR_MIN;
	int i = 1;
	
	printf("     ");
	
	for( ; i <= BOARD_WIDTH; i++)
	{	
		printf("%d   ",i);	
	}
	
	printf("\n");
	printf("====================================\n");

	i = BOARD_ARR_MIN;

	/*Loop through every cell to check its state and draw it accordingly*/
	
	for( ; i <=BOARD_ARR_MAX; i++)
	{
		printf(" %d ", (i+MIN_WIDTH));
		
		for( ; a<= BOARD_ARR_MAX; a++)
		{
			if(board[a][i] == CYAN)
			{			
				printf( "| ");
				printf(COLOUR_CYAN "O " COLOUR_RESET);
			}
			else if(board[a][i] == RED)
			{
				printf( "| ");
				printf(COLOUR_RED "O " COLOUR_RESET);
			}		
			else 
			{
				printf("|   ");
			}
		}
		printf("|   ");
		
		if( i != BOARD_HEIGHT-1)
		{		
		printf("\n------------------------------------\n");
		}
		
		a = BOARD_ARR_MIN;
	}	 
	
	printf("\n====================================\n");
	
}
