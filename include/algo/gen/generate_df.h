/**
 * @file	include/algo/generate_df.h
 * @brief	Headers for the depth-first generation algorithm.
 */

#pragma once

#include "maze.h"
#include "types.h"

int maze_generate_df(uint8_t [MAZE_SIZE_Y][MAZE_SIZE_X], struct perf_data *);
