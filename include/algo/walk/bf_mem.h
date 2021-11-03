/**
 * @file	include/algo/walk/bf_mem.h
 * @brief	Headers for the memory-intensive breadth-first
 *		maze traversal algorithm.
 */

#pragma once

#include "maze.h"
#include "types.h"

int maze_walk_bf_mem(uint8_t [MAZE_SIZE_Y][MAZE_SIZE_X], struct perf_data *);
