/**
 * @file	include/algo/util.h
 * @brief	Headers for algorithm utilities.
 */

#pragma once

#include "maze.h"
#include "types.h"

extern const bool
(*dir_possible[4])(const uint8_t [MAZE_SIZE_Y][MAZE_SIZE_X], const struct coord *,
		   bool);


int neigh_wall_count(const uint8_t [MAZE_SIZE_Y][MAZE_SIZE_X], const struct coord *);

struct coord *get_wall_neighs(const uint8_t [MAZE_SIZE_Y][MAZE_SIZE_X],
			      const struct coord *, size_t *);

struct coord *get_path_neighs(const uint8_t [MAZE_SIZE_Y][MAZE_SIZE_X],
			      const struct coord *, size_t *);
