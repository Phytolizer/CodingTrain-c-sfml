#pragma once

#include "toolbox/vector.h"
#include <SFML/Graphics/Types.h>
typedef struct
{
    float x;
    float y;
    float z;
} Star;

void Star_init(Star* star, sfRenderWindow* window);
void Star_update(Star* star, sfRenderWindow* window, float delta_time);
void Star_draw(Star* star, sfRenderWindow* window);

TOOLBOX_VECTOR_DECLARE(StarVector, Star);
