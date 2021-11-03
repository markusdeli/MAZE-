EXTRA_CFLAGS := \
	-Iinclude \
	-ggdb

SOURCES := \
	src/algo/gen/generate.c \
	src/algo/gen/generate_df.c \
	src/algo/util.c \
	src/algo/walk/bf_mem.c \
	src/algo/walk/df.c \
	src/algo/walk/walk.c \
	src/maze.c \
	src/main.c \
	src/print.c \
	src/stat/stat.c


all:
	gcc $(SOURCES) $(EXTRA_CFLAGS) -o maze
