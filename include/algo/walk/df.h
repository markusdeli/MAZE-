/**
 * @file	include/algo/walk/df.h
 * @brief	Headers for the depth-first maze traversal algorithm.
 */

#pragma once

#include "maze.h"
#include "types.h"

int maze_walk_df(uint8_t [MAZE_SIZE_Y][MAZE_SIZE_X], struct perf_data *);
