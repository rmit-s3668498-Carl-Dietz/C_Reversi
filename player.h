#ifndef PLAYER_H
#define PLAYER_H

#include "utility.h"

typedef enum cell
{
	BLANK, RED, CYAN
}  Cell;

#define COLOUR_RED   "\33[31m"
#define COLOUR_CYAN   "\33[36m"
#define COLOUR_RESET  "\33[0m"

#define NAMELEN 20

typedef struct player
{
	char name[NAMELEN + NULL_SPACE];
	Cell token;
	unsigned score;
}  Player;

void initFirstPlayer(Player * player);
void initSecondPlayer(Player * player, Cell token);


#endif
