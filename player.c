#include "player.h"
#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Code for seeding and using rand adapted for educational purposes from http://en.cppreference.com/w/c/numeric/random/srand */ 

/*This function selects and announces the player who gets the first move*/ 

void initFirstPlayer(struct player *plOne)
{
	int r = 0;
	
	/* A random number is used to decide who goes first */ 
	
	r = rand() % 2;

	if(r == 1)
	{
		plOne->token = CYAN;	
		printf(COLOUR_CYAN "\n\n---%s is cyan!---\n\n" COLOUR_RESET, plOne->name);
	}
	else
	{
		plOne->token = RED;
		printf(COLOUR_RED "\n\n---%s is red!---\n\n" COLOUR_RESET, plOne->name);
	}
	plOne->score = 0;
	printf("%s's score is zero!\n", plOne->name);
}

void initSecondPlayer(struct player *plTwo, Cell PlOtoken)
{
	if(PlOtoken == RED)
	{
		plTwo->token = CYAN;
		printf(COLOUR_CYAN "\n\n---%s is cyan!---\n\n" COLOUR_RESET, plTwo->name);
	}
	else
	{
		plTwo->token = RED;
		printf(COLOUR_RED "\n\n---%s is red!---\n\n" COLOUR_RESET, plTwo->name);
	}
	plTwo->score = 0;
	printf("%s's score is zero!\n", plTwo->name);
}



