/**
 * @file	src/algo/util.c
 * @brief	Algorithm utilities.
 */

#include <stdlib.h>
#include <string.h>

#include "maze.h"
#include "mem.h"
#include "types.h"


/**
 * Determine whether it is possible to build a path over `c`.
 *
 * @param maze	The maze.
 * @param c	The coordinate to check.
 * @returns	`true` if it is possible to go up one tile from `c`.
 */
const static bool up_possible(const uint8_t maze[MAZE_SIZE_Y][MAZE_SIZE_X],
			      const struct coord *c, bool ignore_edges)
{
	bool possible;

	if (c->y <= 0)
		possible = ignore_edges;
	else
		possible = !IS_PATH(maze[c->y - 1][c->x]);

	return possible;
}

/**
 * Determine whether it is possible to build a path beneath `c`.
 *
 * @param maze	The maze.
 * @param c	The coordinate to check.
 * @returns	`true` if it is possible to go down one tile from `c`.
 */
const static bool down_possible(const uint8_t maze[MAZE_SIZE_Y][MAZE_SIZE_X],
				const struct coord *c, bool ignore_edges)
{
	bool possible;

	if (c->y >= MAZE_SIZE_Y - 1)
		possible = ignore_edges;
	else
		possible = !IS_PATH(maze[c->y + 1][c->x]);

	return possible;
}

/**
 * Determine whether it is possible to build a path left to `c`.
 *
 * @param maze	The maze.
 * @param c	The coordinate to check.
 * @returns	`true` if it is possible to go left one tile from `c`.
 */
const static bool left_possible(const uint8_t maze[MAZE_SIZE_Y][MAZE_SIZE_X],
				const struct coord *c, bool ignore_edges)
{
	bool possible;

	if (c->x <= 0)
		possible = ignore_edges;
	else
		possible = !IS_PATH(maze[c->y][c->x - 1]);

	return possible;
}

/**
 * Determine whether it is possible to build a path right to `c`.
 *
 * @param maze	The maze.
 * @param c	The coordinate to check.
 * @returns	`true` if it is possible to go right one tile from `c`.
 */
const static bool right_possible(const uint8_t maze[MAZE_SIZE_Y][MAZE_SIZE_X],
				 const struct coord *c, bool ignore_edges)
{
	bool possible;

	if (c->x >= MAZE_SIZE_X - 1)
		possible = ignore_edges;
	else
		possible = !IS_PATH(maze[c->y][c->x + 1]);

	return possible;
}

/**
 * An array of all neighbor check functions for convenience.
 */
const bool (*dir_possible[4])(const uint8_t [MAZE_SIZE_Y][MAZE_SIZE_X],
			      const struct coord *, bool) = {
	&up_possible,
	&left_possible,
	&down_possible,
	&right_possible
};

/**
 * Check if it is possible to mark `tile` as a path.
 *
 * @param maze	The maze matrix.
 * @param c	The tile coordinate to count the wall neighbors of.
 * @return	`true` if `tile` can be turned into a path.
 */
int neigh_wall_count(uint8_t maze[MAZE_SIZE_Y][MAZE_SIZE_X], const struct coord *c)
{
	int i = 0, neighs = 0;

	for (i = 0; i < 4; i++) {
		if (dir_possible[i](maze, c, true))
			neighs++;
	}

	return neighs;
}

/**
 * Return an array of coordinates of all neighbor walls.
 *
 * @param[in] maze	The maze.
 * @param[in] c		The tile coordinate to check.
 * @param[out] count	Where to store the length of the returned array.
 * @returns		The array of neighbors.
 */
struct coord *get_wall_neighs(uint8_t maze[MAZE_SIZE_Y][MAZE_SIZE_X],
			      const struct coord *c, size_t *count)
{
	int i;
	size_t j;
	struct coord *neighs;
	struct coord *wall_neighs;

	_MALLOC(neighs, sizeof(*neighs) * 4);
	_MALLOC(wall_neighs, sizeof(*wall_neighs) * 3);

	for (i = 0; i < 4; i++)
		memcpy(&neighs[i], c, sizeof(*c));

	neighs[0].y--;
	neighs[1].x--;
	neighs[2].y++;
	neighs[3].x++;

	j = 0;
	for (i = 0; i < 4; i++) {
		if (dir_possible[i](maze, c, false)) {
			memcpy(&wall_neighs[j], &neighs[i], sizeof(*neighs));
			j++;
		}
	}

	free(neighs);
	*count = j;
	return wall_neighs;
}

/**
 * Return an array of coordinates of all neighbor walls.
 *
 * @param[in] maze	The maze.
 * @param[in] c		The tile coordinate to check.
 * @param[out] count	Where to store the length of the returned array.
 * @returns		The array of neighbors.
 */
struct coord *get_path_neighs(uint8_t maze[MAZE_SIZE_Y][MAZE_SIZE_X],
			      const struct coord *c, size_t *count)
{
	int i;
	size_t j;
	struct coord *neighs;
	struct coord *path_neighs;

	_MALLOC(neighs, sizeof(*neighs) * 4);
	_MALLOC(path_neighs, sizeof(*path_neighs) * 4);

	for (i = 0; i < 4; i++)
		memcpy(&neighs[i], c, sizeof(*c));

	neighs[0].y--;
	neighs[1].x--;
	neighs[2].y++;
	neighs[3].x++;

	j = 0;
	for (i = 0; i < 4; i++) {
		if (!dir_possible[i](maze, c, true)) {
			memcpy(&path_neighs[j], &neighs[i], sizeof(*neighs));
			j++;
		}
	}

	free(neighs);
	*count = j;
	return path_neighs;
}
