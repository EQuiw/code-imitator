#include "stdint.h"
typedef int8_t      __int8;
typedef int16_t     __int16;
typedef int32_t     __int32;
typedef int64_t     __int64;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <climits>

#define typeof __typeof__

// following is necessary since clang returns _Bool as bool type during transformations.
typedef bool _Bool;