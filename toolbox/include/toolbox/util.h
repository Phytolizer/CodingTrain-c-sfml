#pragma once

#include "toolbox/internal/namespace.h"
#include <stddef.h>

char* NS_(strdup)(const char* str);
void* NS_(memdup)(const void* mem, size_t size);
