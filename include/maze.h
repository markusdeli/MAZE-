/**
 * @file	include/maze.h
 * @brief	Headers for maze data.
 */

#pragma once

#include "types.h"

/** The maze size. */
#define MAZE_SIZE_X 40
#define MAZE_SIZE_Y 20

#define MAZE_FLAG_PATH		0b00000001
#define MAZE_FLAG_START		0b00000010
#define MAZE_FLAG_END		0b00000100
#define MAZE_FLAG_VISITED	0b00001000
#define MAZE_FLAG_SOLUTION	0b00010000

#define MAZE_SUCCESS 65536

#define IS_PATH(tile) (((tile) & MAZE_FLAG_PATH) != 0)
#define IS_START(tile) (((tile) & MAZE_FLAG_START) != 0)
#define IS_END(tile) (((tile) & MAZE_FLAG_END) != 0)
#define IS_VISITED(tile) (((tile) & MAZE_FLAG_VISITED) != 0)
#define IS_SOLUTION(tile) (((tile) & MAZE_FLAG_SOLUTION) != 0)

#define SET_PATH(tile) ((tile) |= MAZE_FLAG_PATH)
#define SET_WALL(tile) ((tile) &= ~MAZE_FLAG_PATH)
#define SET_START(tile) ((tile) |= MAZE_FLAG_START)
#define SET_END(tile) ((tile) |= MAZE_FLAG_END)
#define SET_VISITED(tile) ((tile) |= MAZE_FLAG_VISITED)
#define SET_SOLUTION(tile) ((tile) |= MAZE_FLAG_SOLUTION)

extern uint8_t maze[MAZE_SIZE_Y][MAZE_SIZE_X];

