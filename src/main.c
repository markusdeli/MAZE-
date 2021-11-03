/**
 * @file	src/main.c
 * @brief	Main program routine.
 */

#include <stdio.h>
#include <stdlib.h>

#include "algo/gen/generate_df.h"
#include "algo/walk/bf_mem.h"
#include "algo/walk/df.h"
#include "algo/walk/walk.h"
#include "maze.h"
#include "print.h"
#include "stat/stat.h"


/**
 * Main program entry point.
 *
 * @param argc		The argument count.
 * @param[in] argv	The argument values.
 * @returns		The program exit code.
 */
int main(int argc, char *argv[])
{
	static const char *usage = "Usage: %s " FUND "seed" RALL "\n";
	char *tmp;
	long int seed;
	struct perf_data perf_dummy;
	if (argc < 2) {
		fprintf(stderr, usage, argv[0]);
		return 1;
	}

	seed = strtoul(argv[1], &tmp, 10);
	if (tmp == argv[1]) {
		fprintf(stderr, usage, argv[0]);
		fprintf(stderr, "Illegal seed value: %s\n", argv[1]);
		return 2;
	}
	srand(seed);

	perf_test_all(1000);

	srand(seed);
	maze_generate_df(maze, &perf_dummy);
	printf("\nBreadth-first:\n");
	maze_walk_bf_mem(maze, &perf_dummy);
	maze_print(maze);

	printf("\nDepth-first:\n");
	maze_walk_df(maze, &perf_dummy);
	maze_print(maze);

	return 0;
}
