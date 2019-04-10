#include "utility.h"

void readRestOfLine()
{
	int ch;
	while(ch = getc(stdin), ch != EOF && ch != '\n')
	{ }

	clearerr(stdin);
}
