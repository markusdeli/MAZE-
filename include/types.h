/**
 * @file	include/types.h
 * @brief	Type / struct headers.
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

struct coord {
	unsigned int x;
	unsigned int y;
};

/**
 * A simple, null-terminated linked list for maze tiles.
 * Used for *bf_mem algorithms.
 */
struct tile_list {
	struct coord tile; /**< A pointer to the tile in the maze
				matrix. */
	struct tile_list *next; /**< The next list element. */
};

/**
 * Stores performance data for a specific algorithm.
 */
struct perf_data {
	clock_t setup_start; /**< The start clock tick of the setup routine. */
	clock_t setup_end; /**< The end clock tick of the setup routine. */
	clock_t walk_start; /**< The start clock tick of the walk routine. */
	clock_t walk_end; /**< The end clock tick of the walk routine. */
	unsigned long int setup_calls; /**< The amount of times the internal
					    setup function has called itself
					    recursively. */
	unsigned long int walk_calls; /**< The amount of times the internal
					   walk function has called itself
					   recursively. */
};
