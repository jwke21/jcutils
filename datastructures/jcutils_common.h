#pragma once

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Avoid conflict with stdbool.h library */
#ifndef _STDBOOL_H
/* Enum that encapsulates true and false booleans */
typedef enum boolean {
    FALSE,
    TRUE
} boolean;
#endif

/* Type for functions that define comparisons between two data elements. */
typedef int (*comparison_func_t)(const void*, const void*);

