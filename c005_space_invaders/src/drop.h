#pragma once

#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>
#include <toolbox/vector.h>

typedef struct
{
    sfCircleShape* shape;
    sfVector2f pos;
} Drop;

TOOLBOX_VECTOR_DECLARE(DropVector, Drop);

void Drop_init(Drop* drop, sfVector2f pos);
void Drop_deinit(Drop drop);
void Drop_show(Drop* drop, sfRenderWindow* window);
