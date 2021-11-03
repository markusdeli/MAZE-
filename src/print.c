/**
 * @file	src/print.c
 * @brief	Printing algorithm w/ color support.
 */

#include <stdio.h>

#include "maze.h"
#include "print.h"
#include "types.h"

/**
 * Print a single tile of a maze.
 *
 * @param flags	The tile flags (matrix index).
 */
static void print_single(uint8_t flags)
{
	if (IS_PATH(flags)) {
		if (IS_START(flags))
			fputs(FBLD CMAG "#" RALL, stdout);
		else if (IS_END(flags))
			fputs(FBLD CGRN "#" RALL, stdout);
		else if (IS_SOLUTION(flags))
			fputs(CCYN "#" RALL, stdout);
		else if (IS_VISITED(flags))
			fputs(CYEL "#" RALL, stdout);
		else
			putchar('#');
	} else {
		putchar(' ');
	}
}

/**
 * Print a maze to the standard output.
 *
 * @param maze	The maze.
 */
void maze_print(uint8_t maze[MAZE_SIZE_Y][MAZE_SIZE_X])
{
	unsigned int i, j;

	putchar('+');
	for (i = 0; i < MAZE_SIZE_X; i++)
		putchar('-');
	putchar('+');
	putchar('\n');

	for (i = 0; i < MAZE_SIZE_Y; i++) {
		putchar('|');
		for (j = 0; j < MAZE_SIZE_X; j++)
			print_single(maze[i][j]);
		putchar('|');
		putchar('\n');
	}

	putchar('+');
	for (i = 0; i < MAZE_SIZE_X; i++)
		putchar('-');
	putchar('+');
	putchar('\n');
}
