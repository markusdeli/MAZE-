/**
 * @file	src/algo/walk/walk.c
 * @brief	Headers for all maze traverssal algorithms combined.
 */

#pragma once

#include "maze.h"
#include "types.h"

struct walk_algo {
	const char *name;
	int (*fn)(uint8_t [MAZE_SIZE_Y][MAZE_SIZE_X], struct perf_data *);
};

extern const struct walk_algo walk_algos[];
extern const int walk_algos_len;
