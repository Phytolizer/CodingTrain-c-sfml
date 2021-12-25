#include "snake.h"
#include "screen.h"
#include "toolbox/math.h"
#include "toolbox/vector.h"
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderTexture.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Types.h>

TOOLBOX_VECTOR_IMPLEMENT(sfVector2fVector, sfVector2f, TOOLBOX_VECTOR_DESTRUCTOR_NONE(sfVector2fVector));

void Snake_init(Snake* snake)
{
    snake->x = 0;
    snake->y = 0;
    snake->dx = 1;
    snake->dy = 0;
    snake->last_update = 0.0f;
    sfVector2fVector_init(&snake->tail);
}

void Snake_deinit(Snake* snake)
{
    sfVector2fVector_deinit(&snake->tail);
}

void Snake_update(Snake* snake, sfRenderWindow* window, float delta_time)
{
    snake->last_update += delta_time;
    if (snake->last_update > 0.5f)
    {
        if (snake->tail.length > 0)
        {
            for (size_t i = snake->tail.length - 1; i > 0; --i)
            {
                snake->tail.data[i] = snake->tail.data[i - 1];
            }
            snake->tail.data[0] = (sfVector2f){.x = snake->x, .y = snake->y};
        }
        snake->last_update = 0.0f;
        snake->x += snake->dx * SCALE;
        snake->y += snake->dy * SCALE;
    }
}
void Snake_draw(Snake* snake, sfRenderWindow* window)
{
    sfRectangleShape* shape = sfRectangleShape_create();
    sfRectangleShape_setPosition(shape, (sfVector2f){.x = snake->x, .y = snake->y});
    sfRectangleShape_setSize(shape, (sfVector2f){.x = SCALE, .y = SCALE});
    sfRectangleShape_setFillColor(shape, sfWhite);
    sfRenderWindow_drawRectangleShape(window, shape, NULL);
    for (size_t i = 0; i < snake->tail.length; ++i)
    {
        sfRectangleShape_setPosition(shape, snake->tail.data[i]);
        sfRenderWindow_drawRectangleShape(window, shape, NULL);
    }
    sfRectangleShape_destroy(shape);
}

void Snake_dir(Snake* snake, int dx, int dy)
{
    snake->dx = dx;
    snake->dy = dy;
}

bool Snake_eat(Snake* snake, Food food)
{
    float d = toolbox_dist(snake->x, snake->y, food.x, food.y);
    if (d < 0.5f)
    {
        sfVector2fVector_push(&snake->tail, (sfVector2f){.x = snake->x, .y = snake->y});
        return true;
    }
    return false;
}
