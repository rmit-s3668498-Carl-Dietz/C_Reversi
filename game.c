#include "game.h"
#include "player.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Player * playGame(Player *plOne, Player *plTwo)
{
	Boolean gameRunning  = TRUE;
	Player * current, * other;
	Cell board[BOARD_HEIGHT][BOARD_WIDTH];
	
	
/* Code for seeding rand adapted for educational purposes from http://en.cppreference.com/w/c/numeric/random/srand */ 

	srand(time(0)); 

/* These functions initialise the players */ 	
	initFirstPlayer(plOne);

	initSecondPlayer(plTwo, plOne->token);	

/* These functions initialise the board and display it onscreen */ 
	initBoard(board);
	
/* Calls initFirstMove function from player.c  to choose who goes first*/
 
	if((plOne->token == RED))
	{
		printf("%s moves first.\n", plOne->name);
		current = plOne;
		other = plTwo;
	}
	else	
	{
		printf("%s moves first.\n", plTwo->name);
		current = plTwo;
		other = plOne;
	}

	/* Central game loops - outer loop for processing the input received from inner loop*/
	
	while (gameRunning == TRUE)
	{	

		if(current->token == RED)
		{
			printf(COLOUR_RED "\n\n Your move, %s\n -----------------\n\n" COLOUR_RESET, current->name);
		}
		else
		{
			printf(COLOUR_CYAN "\n\n Your move, %s\n -----------------\n\n" COLOUR_RESET, current->name);
		}
		
		displayBoard(board, plOne, plTwo);
		
		if(!makeMove(current, board))
		{
			break;
		}
		swapPlayers(&current, &other);
	}
	
	if(current->score > other->score)
	{
		return current;
	}
	if(other->score > current->score)
	{
		return other;
	}
	return NULL;
}



Boolean makeMove(Player * player, Cell board[BOARD_HEIGHT][BOARD_WIDTH])
{ 
	Boolean gameRunning = TRUE;
	long xMove = 0;
	long yMove = 0;
	char input[COORD_LEN + EXTRA_SPACES];
	char *xInput;
	char *yInput;
	int  x = 0;
	int y = 0;
	

	/*Loop for input retrieval*/
	
	while(gameRunning == TRUE)
	{
		/*Prompts for user input*/
		
		printf("\nEnter some coordinates between one and eight, or enter to quit: \n");
		fgets(input, sizeof(input), stdin);
		if(input[strlen(input) - NULL_SPACE] != '\n')
		{
			printf("\n***Invalid Input; Please enter coordinates in the format: 'x,y' where y and x are numbers between one and eight***\n\n");
			readRestOfLine();
			continue;
		}
		input[strlen(input) - NULL_SPACE] = '\0';
		
		/*If an empty line is returned, the game must end*/
		
		if(strcmp(input, "") == 0)
		{
		
			printf("\n\n***The game will now quit***\n\n");
			return FALSE;
			
		}
		
		if(strlen(input) != COORD_LEN)
		{
			printf("\n***Invalid Input; Please enter coordinates in the format: 'x,y' where y and x are numbers between one and eight***\n\n");
			continue;
		}
	
	
		/*The following instructions convert the coordinates entered by the player into ints for use in the gameboard array*/
		
		xInput = strtok(input, ",");

		xMove = strtol(xInput, NULL, BASE_TEN);
		
		if(xMove < MIN_WIDTH || xMove > BOARD_WIDTH)
		{
			printf("\n***Invalid Input; Please enter coordinates in the format: 'x,y' where y and x are numbers between one and eight***\n\n");
			continue;
		}
		
		/*Tokenised string must be validated*/
		
		yInput = strtok(NULL, "");
		
		if(yInput == NULL)
		{
			printf("\n***Invalid Input; Please enter coordinates in the format: 'x,y' where y and x are numbers between one and eight***\n\n");
			continue;
		}

		yMove = strtol(yInput, NULL, BASE_TEN);
		
		if(yMove < MIN_HEIGHT || yMove > BOARD_HEIGHT)
		{
			printf("\n***Invalid Input; Please enter coordinates in the format: 'x,y' where y and x are numbers between one and eight***\n\n");
			continue;
		}
		
		printf("The coordinates entered are %ld and %ld\n", xMove--, yMove--);
		
		x = (int) xMove;
		y = (int) yMove;
		
		/*Validation to ensure player is using a blank tile*/
		
		if(board[xMove][yMove] != BLANK)
		{
			printf("\n***Your piece cannot be placed on this tile***\n\n");
			continue;
		}
		if(applyMove(board, y, x, player->token) != TRUE)
		{
			printf("\n***Illegal Move; Please Try again, %s***\n\n", player->name);
			continue;
		}
		
		gameRunning = FALSE;
	}
	player->score = gameScore(board, player->token);
	
	if(player->token == RED)
	{
		printf(COLOUR_RED "\n================================\n| Your current score is %d, %s |\n================================\n" COLOUR_RESET, player->score, player->name);
	}
	else
	{
		printf(COLOUR_CYAN "\n================================\n| Your current score is %d, %s |\n================================\n" COLOUR_RESET, player->score, player->name);
	}
	return TRUE;
}
	

Boolean applyMove(Cell board[BOARD_HEIGHT][BOARD_WIDTH], int y, int x, Cell token)
{
	Boolean captured = FALSE;
	Boolean captureMade = FALSE;
	Cell antiToken = RED;
	int yChk = y;
	int yTemp = y;
	int xChk = x;
	int xTemp = x;
	Direction dir = NORTH;
	
	/*The colour of friendly and opposing tokens must be known for this function to operate*/
			
	if(token == RED)
	{
		antiToken = CYAN;
	}
		
	for(;dir <=SOUTH_WEST;dir++)
		{
			yChk = y;
			y = yTemp;
			xChk = x;
			x = xTemp;
			captured = FALSE;
			
			/*This Loop checks for opposing tokens in the north direction */
			
			if(dir==NORTH)
			{
				/*This loop goes through every cell above the captured tile*/
				/*It is dependant on results from the nested if statement*/
				
				while(yChk>=0)
				{	
					
					yChk--;
					
					/*This loop executes if there are opposing tokens that could be captured in the NORTH direction*/
					
					if (board[x][yChk] == token && captured == TRUE)
					{
						while(yChk < y)
						{
							yChk++;
							board[x][yChk] = token;
							captureMade = TRUE;
						}
						break;
					}
					
					
					/*This if statement checks for opposing tokens that could be captured*/
					
					else if (board[x][yChk] == antiToken)
					{
						captured = TRUE;
						continue;
					}
					
					else
					{
						break;
					}
				}

			}
			
			/*Variables are reset*/
			
			yChk = y;
			y = yTemp;
			xChk = x;
			x = xTemp;
			captured = FALSE;
			
			
			/*All directions are checked with similar loops as the NORTH loop*/
			
			if(dir==SOUTH)
			{
				while(yChk< BOARD_HEIGHT )
				{	
					
					yChk++;

					if (board[x][yChk] == token && captured == TRUE)
					{
						while(yChk > y)
						{
							yChk--;
							board[x][yChk] = token;
							captureMade = TRUE;
						}
						break;
					}
					
					else if (board[x][yChk] == antiToken)
					{
						captured = TRUE;
						continue;
					}
					
					else
					{
						break;
					}
				}

			}
			
			yChk = y;
			y = yTemp;
			xChk = x;
			x = xTemp;
			captured = FALSE;
			
			if(dir==EAST)
			{
				while(xChk< BOARD_WIDTH)
				{	
					
					xChk++;

					if (board[xChk][y] == token && captured == TRUE)
					{
						while(xChk > x)
						{
							xChk--;
							board[xChk][y] = token;
							captureMade = TRUE;
						}
						break;
					}
					
					else if (board[xChk][y] == antiToken)
					{
						captured = TRUE;
						continue;
					}
					
					else
					{
						break;
					}
				}

			}
			
			yChk = y;
			y = yTemp;
			xChk = x;
			x = xTemp;
			captured = FALSE;
			
			if(dir==WEST)
			{
				while(xChk>=0)
				{	
					
					xChk--;

					if (board[xChk][y] == token && captured == TRUE)
					{
						while(xChk < x)
						{
							xChk++;
							board[xChk][y] = token;
							captureMade = TRUE;
						}
						break;
					}
					
					else if (board[xChk][y] == antiToken)
					{
						captured = TRUE;
						continue;
					}
					
					else
					{
						break;
					}
				}

			}
			
			yChk = y;
			y = yTemp;
			xChk = x;
			x = xTemp;
			captured = FALSE;
			
			if(dir==NORTH_EAST)
			{
				while(yChk>=0 && xChk>=0)
				{	
					
					yChk--;
					xChk--;

					if (board[xChk][yChk] == token && captured == TRUE)
					{
						while(yChk < y && xChk < x)
						{
							yChk++;
							xChk++;
							board[xChk][yChk] = token;
							captureMade = TRUE;
						}
						break;
					}
					
					else if (board[xChk][yChk] == antiToken)
					{
						captured = TRUE;
						continue;
					}
					
					else
					{
						break;
					}
				}

			}
				
			yChk = y;
			y = yTemp;
			xChk = x;
			x = xTemp;
			captured = FALSE;
			
			if(dir==NORTH_WEST)
			{
				while(yChk>=0 && xChk< BOARD_WIDTH)
				{	
					
					yChk--;
					xChk++;

					if (board[xChk][yChk] == token && captured == TRUE)
					{
						while(yChk < y && xChk > x)
						{
							yChk++;
							xChk--;
							board[xChk][yChk] = token;
							captureMade = TRUE;
						}
						break;
					}
						
					else if (board[xChk][yChk] == antiToken)
					{
						captured = TRUE;
						continue;
					}
						
					else
					{
						break;
					}
				}

			}
					
			yChk = y;
			y = yTemp;
			xChk = x;
			x = xTemp;
			captured = FALSE;
			
			if(dir==SOUTH_WEST)
			{
				while(yChk < BOARD_HEIGHT && xChk < BOARD_WIDTH)
				{	
						
					yChk++;
					xChk++;

					if (board[xChk][yChk] == token && captured == TRUE)
					{
						while(yChk > y && xChk > x)
						{
								yChk--;
								xChk--;
								board[xChk][yChk] = token;
								captureMade = TRUE;
						}
						break;
					}
						
					else if (board[xChk][yChk] == antiToken)
					{
						captured = TRUE;
						continue;
					}
					
					else
					{
						break;
					}
				}

			}	
			
			
			yChk = y;
			y = yTemp;
			xChk = x;
			x = xTemp;
			captured = FALSE;
			
			if(dir==SOUTH_EAST)
			{
				while(yChk < BOARD_HEIGHT  && xChk>=0)
				{	
						
					yChk++;
					xChk--;

						if (board[xChk][yChk] == token && captured == TRUE)
						{
							while(yChk > y && xChk < x)
							{
								yChk--;
								xChk++;
								board[xChk][yChk] = token;
								captureMade = TRUE;
							}
							break;
						}
						
						else if (board[xChk][yChk] == antiToken)
						{
							captured = TRUE;
							continue;
						}
						
						else
						{
							break;
						}
					}

				}
				
		}
		
		/** The function returns true if a capture has been made in order to confirm a valid move has been carried out*/
		
		if(captureMade == TRUE)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
		
	}


	/*This function simply calculates the number of tokens of a particular type there are on the board*/
	
unsigned gameScore(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Cell token)
{
	int score = 0;
	int i = 0;
	int a = 0;
	
	for(i = 0; i<BOARD_HEIGHT; i++)
		{
			for(a=0; a<BOARD_WIDTH; a++)
			{
				if(board[a][i]==token)
				{
					score++;
				}
			}
		}
		
		return score;
}

	/*This function simply uses the 'score' value to decide on the game's winner*/
	
void declareWinner(Player * plOne, Player * plTwo)
{
	if(plOne->score > plTwo->score)
	{
		printf("\nThe winner is: %s\n", plOne->name);
	}
	else if(plTwo->score > plOne->score)
	{
		printf("\nThe winner is: %s\n", plTwo->name);
	}
	else
	{
		printf("\nThe game ends in a draw!\n");
	}
}

/*This swaps the pointer to the current player*/

void swapPlayers(Player ** plOne, Player ** plTwo)
{
	Player *plTemp = *plOne;
	*plOne = *plTwo;
	*plTwo = plTemp;
}

