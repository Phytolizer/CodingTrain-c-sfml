#pragma once

#include "food.h"
#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>
#include <stdbool.h>
#include <toolbox/vector.h>

TOOLBOX_VECTOR_DECLARE(sfVector2fVector, sfVector2f);

typedef struct
{
    int x;
    int y;
    int dx;
    int dy;
    float last_update;
    sfVector2fVector tail;
} Snake;

void Snake_init(Snake* snake);
void Snake_deinit(Snake* snake);
void Snake_update(Snake* snake, sfRenderWindow* window, float delta_time);
void Snake_draw(Snake* snake, sfRenderWindow* window);
void Snake_dir(Snake* snake, int dx, int dy);
bool Snake_eat(Snake* snake, Food food);
