#pragma once

#include <SFML/Graphics/Types.h>
#include <stdbool.h>
typedef struct
{
    sfCircleShape* shape;
    int dir;
} Ship;

void Ship_init(Ship* ship, sfRenderWindow* window);
void Ship_deinit(Ship* ship);
void Ship_show(Ship* ship, sfRenderWindow* window);
void Ship_update(Ship* ship, sfRenderWindow* window, float delta_time);
void Ship_move(Ship* ship, int dir);
