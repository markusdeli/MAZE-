/**
 * @file	include/print.h
 * @brief	Printing algorithm w/ color support.
 */

#pragma once

#include "maze.h"
#include "types.h"


/** Reset all terminal formattings. */
#define RALL	"\x1B[0m"
/** Reset bold / bright formatting. */
#define RBLD	"\x1B[21m"
/** Reset dim formatting. */
#define RDIM	"\x1B[22m"
/** Reset underlined formatting. */
#define RUND	"\x1B[24m"
/** Reset blink formatting. */
#define RBLK	"\x1B[25m"
/** Reset inverted color formatting. */
#define RINV	"\x1B[27m"
/** Reset hidden formatting. */
#define RHID	"\x1B[28m"
/** Reset foreground color to default. */
#define RCFG	"\x1B[39m"
/** Reset background color to default. */
#define RCBG	"\x1B[49m"

/** red color code. */
#define CRED	"\x1B[31m"
/** green color code. */
#define CGRN	"\x1B[32m"
/** yellow color code. */
#define CYEL	"\x1B[33m"
/** blue color code. */
#define CBLU	"\x1B[34m"
/** magenta color code. */
#define CMAG	"\x1B[35m"
/** cyan color code. */
#define CCYN	"\x1B[36m"
/** white color code. */
#define CWHT	"\x1B[37m"
/** Reset current color code to default. */
#define CRST	"\x1B[39m"

/** bold font code. */
#define FBLD	"\x1B[1m"
/** dim font code. */
#define FDIM	"\x1B[2m"
/** underlined font code. */
#define FUND	"\x1B[4m"
/** blinking fond code. */
#define FBLK	"\x1B[5m"
/** inverted color font code. */
#define FINV	"\x1B[7m"
/** hidden font code. */
#define FHID	"\x1B[8m"

void maze_print(uint8_t [MAZE_SIZE_Y][MAZE_SIZE_X]);
