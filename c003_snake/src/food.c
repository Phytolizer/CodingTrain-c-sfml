#include "food.h"
#include "screen.h"
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/System/Vector2.h>
#include <toolbox/random.h>

void Food_pick_location(Food* food, sfRenderWindow* window)
{
    sfVector2u size = sfRenderWindow_getSize(window);
    food->x = toolbox_random_int_range(0, size.x / SCALE - 1) * SCALE;
    food->y = toolbox_random_int_range(0, size.y / SCALE - 1) * SCALE;
}

void Food_draw(Food* food, sfRenderWindow* window)
{
    sfRectangleShape* shape = sfRectangleShape_create();
    sfRectangleShape_setPosition(shape, (sfVector2f){.x = food->x, .y = food->y});
    sfRectangleShape_setFillColor(shape, sfColor_fromRGB(255, 0, 100));
    sfRectangleShape_setSize(shape, (sfVector2f){.x = SCALE, .y = SCALE});
    sfRenderWindow_drawRectangleShape(window, shape, NULL);
    sfRectangleShape_destroy(shape);
}
