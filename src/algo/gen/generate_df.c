/**
 * @file	src/algo/generate_df.c
 * @brief	Depth-first maze generator algorithm
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "algo/gen/generate.h"
#include "algo/gen/generate_df.h"
#include "algo/util.h"
#include "maze.h"
#include "mem.h"
#include "types.h"


/**
 * Internal implementation of the depth-first generation algorithm.
 *
 * @param[in,out] maze		The maze.
 * @param[in] current_coord	The current tile coordinate.
 * @return			An error code, or `0` on success.
 */
static int __maze_generate_df(uint8_t maze[MAZE_SIZE_Y][MAZE_SIZE_X],
			     struct coord *current_coord,
			     unsigned int current_depth,
			     struct coord **deepest,
			     unsigned int *max_depth,
			     struct perf_data *perf)
{
	unsigned int i;
	int err = 0;
	static const unsigned int perms[6][3] = {
		{0, 1, 2},
		{0, 2, 1},
		{1, 0, 2},
		{1, 2, 0},
		{2, 0, 1},
		{2, 1, 0}
	};
	const unsigned int *perm = perms[rand() % 6];
	struct coord *wall_neighs;
	size_t wall_neighs_len;

	perf->setup_calls++;

	if (IS_VISITED(maze[current_coord->y][current_coord->x]))
		return 0;

	if (current_depth > *max_depth) {
		*max_depth = current_depth;
		memcpy(*deepest, current_coord, sizeof(**deepest));
	}

	SET_PATH(maze[current_coord->y][current_coord->x]);
	SET_VISITED(maze[current_coord->y][current_coord->x]);

	wall_neighs = get_wall_neighs(maze, current_coord, &wall_neighs_len);
	for (i = 0; i < 3; i++) {
		if (perm[i] >= wall_neighs_len)
			continue;
		if (neigh_wall_count(maze, &wall_neighs[perm[i]]) < 3)
			continue;

		err = __maze_generate_df(maze, &wall_neighs[perm[i]],
					current_depth + 1, deepest, max_depth,
					perf);
		if (err)
			break;
	}

	free(wall_neighs);
	return err;
}

/**
 * Generate a new maze (depth-first).
 *
 * @param[out] maze	Where to store the maze.
 * @param[out] perf	Where to store performance data.
 * @return		An error code, or `0` on success.
 */
int maze_generate_df(uint8_t maze[MAZE_SIZE_Y][MAZE_SIZE_X], struct perf_data *perf)
{
	unsigned int i, max_depth = 0;
	int err;
	struct coord start = {
		.x = 0,
		.y = 0
	};
	struct coord *deepest;

	_MALLOC(deepest, sizeof(*deepest));
	deepest->x=0;
	deepest->y=0;

	for (i = 0; i < MAZE_SIZE_Y; i++)
		memset(&maze[i][0], 0, sizeof(**maze) * MAZE_SIZE_X);

	SET_START(maze[start.y][start.x]);

	err = __maze_generate_df(maze, &start, 0, &deepest, &max_depth, perf);
	if (!err)
		SET_END(maze[deepest->y][deepest->x]);

	free(deepest);

	return err;
}
