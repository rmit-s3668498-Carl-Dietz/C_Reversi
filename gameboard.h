#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "player.h"

#define BOARD_ARR_MIN 0
#define BOARD_ARR_MAX 7

#define COORD_LEN 3
#define START_CELL 3

#define BOARD_HEIGHT 8
#define MIN_HEIGHT 1
#define HALF_HEIGHT (BOARD_HEIGHT/2)

#define BOARD_WIDTH BOARD_HEIGHT
#define MIN_WIDTH MIN_HEIGHT 
#define HALF_WIDTH HALF_HEIGHT

void initBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH]);
void displayBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Player * first, Player * second);

#endif
