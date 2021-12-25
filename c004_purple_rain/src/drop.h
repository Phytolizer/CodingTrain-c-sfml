#pragma once

#include "toolbox/vector.h"
#include <SFML/Graphics/Types.h>
typedef struct
{
    sfRectangleShape* shape;
    float z;
    float yspeed;
} Drop;

TOOLBOX_VECTOR_DECLARE(DropVector, Drop);

void Drop_init(Drop* drop, sfRenderWindow* window);
void Drop_deinit(Drop drop);
void Drop_fall(Drop* drop, sfRenderWindow* window, float delta_time);
void Drop_show(Drop* drop, sfRenderWindow* window);
