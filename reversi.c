#include "utility.h"
#include "reversi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
char slt[MENU_SIZE];
Boolean menuRunning = TRUE;

/*Loop to keep the menu running*/

while(menuRunning == TRUE)
{
	printf("\nWelcome to Reversi!\n===========\nSelect an Option:\n1.Start New Game\n2.Quit\nPlease Enter Your Choice: ");
	
	/*User input is used to decide next action*/
	
	fgets(slt, sizeof(slt), stdin);
	
	/*Validation*/
	
	if (slt[strlen(slt)-1] != '\n')
	{	
		readRestOfLine();
	}
	
	else if (slt[0] == '\n')
	{
		printf("\n***No Entry***\n");
		continue;
	}
	
	else
	{
		(slt[strlen(slt)-1] = '\0');
		printf("%s\n",slt);
	}
	
	
	if (strcmp(slt, "1")==0)
	{
		printf("\n\nYou Entered 1; A new game will now begin.\n\nEnter name for Player One: \n" );
		
		/*Call function to start a game*/
		
		runGame();
		
		continue;
	}
	
	else if (strcmp(slt, "2")==0)
	{
		printf("You entered 2; The Game Will Now Quit\n");
		break;
	}
	else
	{
		printf("\n***Invalid Entry***\n");
		continue;
	}
}
return EXIT_SUCCESS;
}

void runGame()
{
	Player plOne, plTwo, * winner;
		
	fgets(plOne.name, sizeof(plOne.name), stdin);
		
	if (plOne.name[strlen(plOne.name)-NULL_SPACE] != '\n')
	{
	printf("Your Entry is too long; it will be shortened\n");
	readRestOfLine();
	}
		
	/*Remove trailing '\n'*/
		
	strtok(plOne.name, "\n");

	printf("\nPlayer One is now: %s\nEnter name for Player Two: \n", plOne.name);	
	fgets(plTwo.name, sizeof(plTwo.name), stdin);

	if (plTwo.name[strlen(plTwo.name)-NULL_SPACE] != '\n')
	{
	printf("Your Entry is too long; it will be shortened\n");
	readRestOfLine();
	}

	/*Remove trailing '\n'*/
	strtok(plTwo.name, "\n");
		
	printf("Player Two is now: %s\nThe Game Will Now Commence!\n", plTwo.name);

	/*The game begins*/
		
	winner = playGame(&plOne, &plTwo);
	
	if(winner == NULL)
	{
		printf("\n\n|||The game has ended in a draw!|||\n");
	}
	else
	{
		if(winner->token == RED)
		{
			printf(COLOUR_RED "\n--------------------\n The winner is: %s\n--------------------\n\n" COLOUR_RESET, winner->name);
		}
		else
		{
			printf(COLOUR_CYAN "\n--------------------\n The winner is: %s\n--------------------\n\n" COLOUR_RESET, winner->name);
		}
	}
}