/**
 * @file	include/algo/generate.h
 * @brief	Headers for the generation algorithms.
 */

#pragma once

#include "maze.h"

/**
 * A bundle of all maze generation algorithms.
 */
struct gen_algo {
	const char *name;
	int (*fn)(uint8_t [MAZE_SIZE_Y][MAZE_SIZE_X], struct perf_data *);
};

extern const struct gen_algo gen_algos[];
