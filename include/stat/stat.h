/**
 * @file	include/stat/stat.h
 * @brief	Headers for performance statistics.
 */

#pragma once

#include "maze.h"
#include "types.h"
#include "algo/gen/generate.h"
#include "algo/walk/walk.h"

struct algo {
	const struct gen_algo *gen;
	const struct walk_algo *walk;
};

extern const struct algo algos[];

extern const int algos_len;

extern struct perf_data **performance_records;

int do_perf_test(const struct algo *, struct perf_data *, unsigned int);

int perf_test_all(unsigned int);
