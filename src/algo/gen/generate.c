/**
 * @file	src/algo/generate.c
 * @brief	Maze generation algorithm.
 */

#include <stdlib.h>

#include "algo/gen/generate.h"
#include "algo/gen/generate_df.h"
#include "maze.h"
#include "types.h"

const struct gen_algo gen_algos[] = {
	{
		.name = "df",
		.fn = &maze_generate_df
	}
};

const int gen_algos_len = sizeof(gen_algos) / sizeof(gen_algos[0]);
