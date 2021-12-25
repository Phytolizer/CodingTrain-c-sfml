#include "toolbox/math.h"
#include <math.h>

float NS_(map_float)(float value, float in_min, float in_max, float out_min, float out_max)
{
    return out_min + (out_max - out_min) * (value - in_min) / (in_max - in_min);
}

int NS_(map_int)(int value, int in_min, int in_max, int out_min, int out_max)
{
    return (int)((long)out_min +
                 ((long)out_max - (long)out_min) * ((long)value - (long)in_min) / ((long)in_max - (long)in_min));
}

float NS_(dist)(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrtf(dx * dx + dy * dy);
}
