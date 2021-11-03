/**
 * @file	src/algo/walk/walk.c
 * @brief	All maze traversal algorithms combined.
 */

#include "algo/walk/bf_mem.h"
#include "algo/walk/df.h"
#include "algo/walk/walk.h"
#include "maze.h"
#include "types.h"


/**
 * All maze traversal / solving algorithms combined.
 */
const struct walk_algo walk_algos[] = {
	{
		.name = "bf_mem",
		.fn = &maze_walk_bf_mem
	},
	{
		.name = "df",
		.fn = &maze_walk_df
	}
};

const int walk_algos_len = sizeof(walk_algos) / sizeof(walk_algos[0]);
