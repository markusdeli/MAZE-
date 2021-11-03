/**
 * @file	src/stat/stat.c
 * @brief	Performance statistics.
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "algo/gen/generate_df.h"
#include "algo/walk/df.h"
#include "maze.h"
#include "mem.h"
#include "stat/stat.h"
#include "types.h"


/** All algorithms (generators and walkers) combined. */
const struct algo algos[] = {
	{
		.gen = &gen_algos[0],
		.walk = &walk_algos[0]
	},
	{
		.gen = &gen_algos[0],
		.walk = &walk_algos[1]
	}
};

/** The length of the algorithm array. */
const int algos_len = sizeof(algos) / sizeof(algos[0]);


/**
 * Do a single performance run.
 *
 * @param perf		Where to store performance data.
 * @param generator	The generator algorithm to use.
 * @param walker	The traversal / solving algorithm to use.
 * @returns		An error code.
 */
static int perf_test_single(struct perf_data *perf,
			    const struct gen_algo *generator,
			    const struct walk_algo *walker)
{
	int err;

	perf->setup_start = clock();
	err = generator->fn(maze, perf);
	perf->setup_end = clock();

	if (err == 0 || err == MAZE_SUCCESS) {
		perf->walk_start = clock();
		err = walker->fn(maze, perf);
		perf->walk_end = clock();
	}

	return err;
}

/**
 * Start evaluating one algorithm.
 *
 * @param algo		The algorithm to use.
 * @param perf_index	Start address of the performance data array to write to.
 * @param n_runs	How many to perform (and the length of `perf_index`).
 * @returns		An error code.
 */
int do_perf_test(const struct algo *algo, struct perf_data *perf_index,
		 unsigned int n_runs)
{
	int err = 0;
	unsigned int i;

	memset(perf_index, 0, sizeof(*perf_index) * n_runs);

	for (i = 0; i < n_runs; i++) {
		err = perf_test_single(&perf_index[i],
				       algo->gen, algo->walk);

		if (err != 0 && err != MAZE_SUCCESS)
			break;
	}

	return err;
}

static void perf_test_print(const struct algo *algo,
			    const struct perf_data *data, int len)
{
	int i;
	unsigned long int clock_sum_gen = 0,
			  clock_sum_walk = 0,
			  calls_sum_gen = 0,
			  calls_sum_walk = 0;

	for (i = 0; i < len; i++) {
		clock_sum_gen += (data[i].setup_end - data[i].setup_start);
		clock_sum_walk += (data[i].walk_end - data[i].walk_start);
		calls_sum_gen += data[i].setup_calls;
		calls_sum_walk += data[i].walk_calls;
	}

	printf("Generator %s:\n", algo->gen->name);
	printf("  avg CPU cycles:      %ld\n", clock_sum_gen / len);
	printf("  avg recursive calls: %ld\n", calls_sum_gen / len);
	printf("Walker %s:\n", algo->walk->name);
	printf("  avg CPU cycles:      %ld\n", clock_sum_walk / len);
	printf("  avg recursive calls: %ld\n\n", calls_sum_walk / len);
}

int perf_test_all(unsigned int n_runs)
{
	int i, err;
	struct perf_data **perf;

	_MALLOC(perf, sizeof(*perf) * algos_len);

	for (i = 0; i < algos_len; i++) {
		_MALLOC(perf[i], sizeof(**perf) * n_runs);

		err = do_perf_test(&algos[i], perf[i], n_runs);
		perf_test_print(&algos[i], perf[i], n_runs);

		if (err != 0 && err != MAZE_SUCCESS)
			break;

		free(perf[i]);
	}

	free(perf);

	return err;
}
