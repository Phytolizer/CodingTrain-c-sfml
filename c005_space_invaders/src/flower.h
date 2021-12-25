#pragma once

#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>
#include <toolbox/vector.h>

typedef struct
{
    sfCircleShape* shape;
} Flower;

TOOLBOX_VECTOR_DECLARE(FlowerVector, Flower);

void Flower_init(Flower* flower, sfVector2f pos);
void Flower_update(Flower* flower, sfRenderWindow* window, float deltaTime);
void Flower_show(Flower* flower, sfRenderWindow* window);
void Flower_deinit(Flower flower);
