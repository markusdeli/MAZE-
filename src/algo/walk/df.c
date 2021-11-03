/**
 * @file	src/algo/walk/df.c
 * @brief	Depth-first maze traversal algorithm.
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "algo/walk/df.h"
#include "algo/util.h"
#include "maze.h"
#include "types.h"


static int __maze_walk_df(uint8_t maze[MAZE_SIZE_Y][MAZE_SIZE_X],
			 struct coord *current, struct perf_data *perf)
{
	int i, err = 0;
	struct coord *dirs;
	uint8_t *current_tile;
	size_t dirs_len;

	perf->walk_calls++;
	current_tile = &maze[current->y][current->x];

	if (IS_VISITED(*current_tile) || !IS_PATH(*current_tile))
		return 0;
	SET_VISITED(*current_tile);

	if (IS_END(*current_tile)) {
		SET_SOLUTION(*current_tile);
		return MAZE_SUCCESS;
	}

	dirs = get_path_neighs(maze, current, &dirs_len);
	for (i = 0; i < dirs_len; i++) {
		err = __maze_walk_df(maze, &dirs[i], perf);

		if (err) {
			if (err == MAZE_SUCCESS)
				SET_SOLUTION(*current_tile);
			break;
		}
	}
	free(dirs);

	return err;
}

int maze_walk_df(uint8_t maze[MAZE_SIZE_Y][MAZE_SIZE_X], struct perf_data *perf)
{
	int i, j, err = 0;
	struct coord current = {
		.x = 0,
		.y = 0
	};

	for (i = 0; i < MAZE_SIZE_Y; i++) {
		for (j = 0; j < MAZE_SIZE_X; j++)
			maze[i][j] &= ~MAZE_FLAG_VISITED;
	}

	err = __maze_walk_df(maze, &current, perf);
	if (err == MAZE_SUCCESS)
		err = 0;

	return err;
}
