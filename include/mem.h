#pragma once

#include <errno.h>
#include <stdio.h>
#include <string.h>

#define _MALLOC(ptr, size) ({				\
	ptr = (typeof(ptr))malloc(size);		\
	if (!(ptr)) {					\
		fputs(strerror(ENOMEM), stderr);	\
		exit(ENOMEM);				\
	}						\
})
