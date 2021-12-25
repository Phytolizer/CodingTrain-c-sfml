#include "star.h"
#include "toolbox/random.h"
#include <SFML/Graphics/CircleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>
#include <toolbox/math.h>
#include <toolbox/vector.h>

TOOLBOX_VECTOR_IMPLEMENT(StarVector, Star, TOOLBOX_VECTOR_DESTRUCTOR_NONE(StarVector));

void Star_init(Star* star, sfRenderWindow* window)
{
    sfVector2u window_size = sfRenderWindow_getSize(window);
    star->x = toolbox_random_float_range(-(float)window_size.x / 2, (float)window_size.x / 2);
    star->y = toolbox_random_float_range(-(float)window_size.y / 2, (float)window_size.y / 2);
    star->z = toolbox_random_float_range(0.0f, (float)window_size.x);
}

void Star_update(Star* star, sfRenderWindow* window, float delta_time)
{
    sfVector2u window_size = sfRenderWindow_getSize(window);
    star->z -= delta_time * window_size.x;
    if (star->z < 1.0f)
    {
        star->x = toolbox_random_float_range(-(float)window_size.x / 2, (float)window_size.x / 2);
        star->y = toolbox_random_float_range(-(float)window_size.y / 2, (float)window_size.y / 2);
        star->z = (float)window_size.x;
    }
}

void Star_draw(Star* star, sfRenderWindow* window)
{
    sfVector2u window_size = sfRenderWindow_getSize(window);
    float x = toolbox_map_float(star->x / star->z, -1.0f, 1.0f, 0.0f, (float)window_size.x);
    float y = toolbox_map_float(star->y / star->z, -1.0f, 1.0f, 0.0f, (float)window_size.y);
    float r = toolbox_map_float(star->z, 0.0f, (float)window_size.x, 8.0f, 0.0f);

    sfCircleShape* shape = sfCircleShape_create();
    sfCircleShape_setRadius(shape, r);
    sfCircleShape_setPosition(shape, (sfVector2f){.x = x, .y = y});
    sfCircleShape_setFillColor(shape, sfWhite);
    sfCircleShape_setOrigin(shape, (sfVector2f){.x = r, .y = r});
    sfRenderWindow_drawCircleShape(window, shape, NULL);
    sfCircleShape_destroy(shape);
}
