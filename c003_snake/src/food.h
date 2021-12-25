#pragma once

#include <SFML/Graphics/Types.h>

typedef struct
{
    float x;
    float y;
} Food;

void Food_draw(Food* food, sfRenderWindow* window);
void Food_pick_location(Food* food, sfRenderWindow* window);
