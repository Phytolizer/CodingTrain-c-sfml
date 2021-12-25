#pragma once

#include "toolbox/internal/namespace.h"

float NS_(map_float)(float value, float in_min, float in_max, float out_min, float out_max);
int NS_(map_int)(int value, int in_min, int in_max, int out_min, int out_max);

float NS_(dist)(float x1, float y1, float x2, float y2);
