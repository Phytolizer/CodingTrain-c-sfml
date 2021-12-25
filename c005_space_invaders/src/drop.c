#include "drop.h"
#include <SFML/Graphics/CircleShape.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/RenderWindow.h>

TOOLBOX_VECTOR_IMPLEMENT(DropVector, Drop, TOOLBOX_VECTOR_DESTRUCTOR(DropVector, Drop_deinit));

void Drop_init(Drop* drop, sfVector2f pos)
{
    drop->shape = sfCircleShape_create();
    sfCircleShape_setRadius(drop->shape, 10);
    sfCircleShape_setFillColor(drop->shape, sfColor_fromRGB(50, 0, 200));
    sfCircleShape_setPosition(drop->shape, pos);
}

void Drop_deinit(Drop drop)
{
    sfCircleShape_destroy(drop.shape);
}

void Drop_show(Drop* drop, sfRenderWindow* window)
{
    sfRenderWindow_drawCircleShape(window, drop->shape, NULL);
}
