#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <assert.h>

typedef enum boolean
{
	FALSE = 0,
	TRUE
} Boolean;

#define NEW_LINE_SPACE 1
#define NULL_SPACE 1

#define EXTRA_SPACES (NEW_LINE_SPACE + NULL_SPACE)

#define EMPTY STRING ""

void readRestOfLine();

#endif
