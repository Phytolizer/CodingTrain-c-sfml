#include "ship.h"
#include <SFML/Graphics/CircleShape.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/System/Vector2.h>
#include <math.h>

void Ship_init(Ship* ship, sfRenderWindow* window)
{
    ship->shape = sfCircleShape_create();
    ship->dir = 0;
    sfVector2u size = sfRenderWindow_getSize(window);
    sfCircleShape_setPointCount(ship->shape, 3);
    sfCircleShape_setPosition(ship->shape, (sfVector2f){
                                               .x = (float)size.x / 2.0f,
                                               .y = (float)size.y,
                                           });
    float sideLength = 20;
    sfCircleShape_setOrigin(ship->shape, (sfVector2f){
                                             .x = sideLength / 2,
                                             .y = (sideLength / 2) * sqrtf(3),
                                         });
    sfCircleShape_setRadius(ship->shape, (sideLength / 2) / sinf(M_PI / 3));
    sfCircleShape_setFillColor(ship->shape, sfWhite);
}

void Ship_deinit(Ship* ship)
{
    sfCircleShape_destroy(ship->shape);
}

void Ship_show(Ship* ship, sfRenderWindow* window)
{
    sfRenderWindow_drawCircleShape(window, ship->shape, NULL);
}

void Ship_update(Ship* ship, sfRenderWindow* window, float delta_time)
{
    sfCircleShape_move(ship->shape, (sfVector2f){.x = ship->dir * delta_time * 200, .y = 0.0f});
}

void Ship_move(Ship* ship, int dir)
{
    if (dir < 0)
    {
        if (ship->dir >= 0)
        {
            ship->dir--;
        }
    }
    else if (dir > 0)
    {
        if (ship->dir <= 0)
        {
            ship->dir++;
        }
    }
}
