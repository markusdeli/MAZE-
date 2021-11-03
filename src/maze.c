/**
 * @file	src/maze.c
 * @brief	Maze data.
 */

#include "maze.h"
#include "types.h"

/**
 * The maze.
 *
 * Each column represents a tile, see `maze.h` for details about flags.
 */
uint8_t maze[MAZE_SIZE_Y][MAZE_SIZE_X];
