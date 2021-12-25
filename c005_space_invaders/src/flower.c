#include "flower.h"
#include <SFML/Graphics/CircleShape.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/RenderWindow.h>

TOOLBOX_VECTOR_IMPLEMENT(FlowerVector, Flower, TOOLBOX_VECTOR_DESTRUCTOR(FlowerVector, Flower_deinit));

void Flower_init(Flower* flower, sfVector2f pos)
{
    flower->shape = sfCircleShape_create();
    sfCircleShape_setFillColor(flower->shape, sfColor_fromRGB(255, 0, 200));
    sfCircleShape_setOrigin(flower->shape, (sfVector2f){30, 30});
    sfCircleShape_setPosition(flower->shape, pos);
    sfCircleShape_setRadius(flower->shape, 30);
    sfCircleShape_setOutlineColor(flower->shape, sfBlack);
    sfCircleShape_setOutlineThickness(flower->shape, 1);
}

void Flower_update(Flower* flower, sfRenderWindow* window, float deltaTime)
{
}

void Flower_show(Flower* flower, sfRenderWindow* window)
{
    sfRenderWindow_drawCircleShape(window, flower->shape, NULL);
}

void Flower_deinit(Flower flower)
{
    sfCircleShape_destroy(flower.shape);
}
