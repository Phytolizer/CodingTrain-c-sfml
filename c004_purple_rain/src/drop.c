#include "drop.h"
#include "toolbox/math.h"
#include "toolbox/random.h"
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <toolbox/vector.h>

TOOLBOX_VECTOR_IMPLEMENT(DropVector, Drop, TOOLBOX_VECTOR_DESTRUCTOR(DropVector, Drop_deinit));

void Drop_init(Drop* drop, sfRenderWindow* window)
{
    sfVector2u size = sfRenderWindow_getSize(window);
    drop->shape = sfRectangleShape_create();
    drop->z = toolbox_random_float_range(0, 20);
    sfRectangleShape_setFillColor(drop->shape, sfColor_fromRGB(138, 43, 226));
    sfRectangleShape_setPosition(drop->shape, (sfVector2f){
                                                  .x = toolbox_random_float_range(0, size.x),
                                                  .y = toolbox_random_float_range(-500, -50),
                                              });
    float thick = toolbox_map_float(drop->z, 0, 20, 1, 3);
    sfRectangleShape_setSize(drop->shape, (sfVector2f){
                                              .x = thick,
                                              .y = toolbox_map_float(drop->z, 0, 20, 10, 20),
                                          });
    sfRectangleShape_setOrigin(drop->shape, (sfVector2f){.x = thick / 2, .y = 0});
    drop->yspeed = toolbox_map_float(drop->z, 0, 20, 400, 1000);
}

void Drop_deinit(Drop drop)
{
    sfRectangleShape_destroy(drop.shape);
}

void Drop_fall(Drop* drop, sfRenderWindow* window, float delta_time)
{
    sfRectangleShape_move(drop->shape, (sfVector2f){.x = 0, .y = drop->yspeed * delta_time});
    float grav = toolbox_map_float(drop->z, 0, 20, 0, 200);
    drop->yspeed += grav * delta_time;
    sfVector2f pos = sfRectangleShape_getPosition(drop->shape);
    sfVector2u size = sfRenderWindow_getSize(window);
    if (pos.y > size.y)
    {
        pos.y = toolbox_random_float_range(-200, -100);
        sfRectangleShape_setPosition(drop->shape, pos);
        drop->yspeed = toolbox_map_float(drop->z, 0, 20, 400, 1000);
    }
}

void Drop_show(Drop* drop, sfRenderWindow* window)
{
    sfRenderWindow_drawRectangleShape(window, drop->shape, NULL);
}
