#ifndef GAME_H
#define GAME_H

#include "gameboard.h"

#define BASE_TEN 10
#define ARRAY_LENGTH 7

typedef enum direction
{
	NORTH, SOUTH, EAST, WEST, NORTH_EAST, NORTH_WEST, SOUTH_EAST, SOUTH_WEST
} Direction;

Player * playGame(Player * first, Player * second);
Boolean makeMove(Player * player, Cell board[BOARD_HEIGHT][BOARD_WIDTH]);
Boolean applyMove(Cell board[BOARD_HEIGHT][BOARD_WIDTH], int y, int x, Cell token);
unsigned gameScore(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Cell token);
void declareWinner(Player * plOne, Player * plTwo);
void swapPlayers(Player ** first, Player ** second);

#endif
