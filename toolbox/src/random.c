#include "toolbox/random.h"
#include "toolbox/math.h"
#include <sodium/randombytes.h>

float NS_(random_float)(void)
{
    return (float)randombytes_random() / (float)randombytes_BYTES_MAX;
}

float NS_(random_float_range)(float min, float max)
{
    return NS_(map_float)(NS_(random_float)(), 0.0f, 1.0f, min, max);
}

int NS_(random_int)(void)
{
    return (int)randombytes_random();
}

int NS_(random_int_range)(int min, int max)
{
    return NS_(map_int)(NS_(random_int)(), INT_MIN, INT_MAX, min, max);
}
