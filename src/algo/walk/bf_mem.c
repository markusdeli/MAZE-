/**
 * @file	src/algo/walk/bf_mem.c
 * @brief	Memory-intensive, breadth-first maze traversal algorithm.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "algo/util.h"
#include "algo/walk/bf_mem.h"
#include "maze.h"
#include "mem.h"
#include "types.h"


/**
 * Add a tile to a list if it is not visited and set its visited flag.
 *
 * @param maze	The maze.
 * @param coord	The tile to add/update.
 */
static void tile_add_if_legal(uint8_t maze[MAZE_SIZE_Y][MAZE_SIZE_X],
			      struct tile_list **list, struct coord *coord)
{
	if (!IS_VISITED(maze[coord->y][coord->x])) {
		if (*list == NULL) {
			_MALLOC(*list, sizeof(**list));
		} else {
			_MALLOC((*list)->next, sizeof(**list));
			*list = (*list)->next;
		}

		memcpy(&(*list)->tile, coord, sizeof((*list)->tile));
		(*list)->next = NULL;

		SET_VISITED(maze[coord->y][coord->x]);
	}

}

/**
 * Update the tile that is part of the solution path.
 *
 * @param maze	The maze.
 * @param list	The list of all tiles at the current depth.
 */
static void update_solution(uint8_t maze[MAZE_SIZE_Y][MAZE_SIZE_X],
			    const struct tile_list *list)
{
	unsigned int i;
	bool found = false;
	const struct coord *tile;
	struct coord *neighs;
	size_t neighs_len;

	while (list != NULL && !found) {
		tile = &list->tile;

		neighs = get_path_neighs(maze, tile, &neighs_len);
		for (i = 0; i < neighs_len; i++) {
			if (IS_SOLUTION(maze[neighs[i].y][neighs[i].x])) {
				SET_SOLUTION(maze[tile->y][tile->x]);
				found = true;
				break;
			}
		}
		free(neighs);

		list = list->next;
	}
}

/**
 * Free memory from a tile list.
 *
 * @param list	The list.
 */
static void free_list(struct tile_list *list)
{
	if (list->next != NULL)
		free_list(list->next);
	free(list);
}

/**
 * Internal function for `maze_walk_bf_mem` (one recursive call per depth level).
 *
 * @param[in,out] maze		The maze.
 * @param[out] perf		Where to write performance statistics.
 * @param[in] current_list	A list of all tiles at the current depth.
 */
static int __maze_walk_bf_mem(uint8_t maze[MAZE_SIZE_Y][MAZE_SIZE_X],
			     struct perf_data *perf,
			     const struct tile_list *current_list)
{
	int err = 0;
	unsigned int i;
	size_t neighs_len;
	struct tile_list *next_list = NULL,
			 *next_list_cur = NULL;
	const struct tile_list *current_list_cur = current_list;
	const struct coord *coord_cur;
	struct coord *neighs;

	perf->walk_calls++;

	while (current_list_cur != NULL) {
		coord_cur = &current_list_cur->tile;

		if (IS_END(maze[coord_cur->y][coord_cur->x])) {
			err = MAZE_SUCCESS;
			SET_SOLUTION(maze[coord_cur->y][coord_cur->x]);
			break;
		}

		neighs = get_path_neighs(maze, coord_cur, &neighs_len);
		for (i = 0; i < neighs_len; i++) {
			tile_add_if_legal(maze, &next_list_cur, &neighs[i]);
			if (next_list == NULL)
				next_list = next_list_cur;
		}
		free(neighs);

		current_list_cur = current_list_cur->next;
	}

	if (!err) {
		err = __maze_walk_bf_mem(maze, perf, next_list);
		free_list(next_list);
	}

	if (err == MAZE_SUCCESS)
		update_solution(maze, current_list);

	return err;
}

/**
 * Walk through a maze and find the path to the exit.
 *
 * @param[in,out] maze	The maze.
 * @param[out] perf	Where to write performance statistics.
 */
int maze_walk_bf_mem(uint8_t maze[MAZE_SIZE_Y][MAZE_SIZE_X], struct perf_data *perf)
{
	int i, j;
	struct tile_list start_list = {
		.tile = {
			.x = 0,
			.y = 0
		},
		.next = NULL
	};

	for (i = 0; i < MAZE_SIZE_Y; i++) {
		for (j = 0; j < MAZE_SIZE_X; j++)
			maze[i][j] &= ~MAZE_FLAG_VISITED;
	}

	return __maze_walk_bf_mem(maze, perf, &start_list);
}
