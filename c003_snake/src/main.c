#include "screen.h"
#include "snake.h"
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/View.h>
#include <SFML/System/Clock.h>
#include <SFML/Window/Event.h>
#include <SFML/Window/Keyboard.h>
#include <SFML/Window/Window.h>
#include <toolbox/random.h>

int main(void)
{
    sfRenderWindow* window =
        sfRenderWindow_create((sfVideoMode){.bitsPerPixel = 32, .width = SCREEN_WIDTH, .height = SCREEN_HEIGHT},
                              "Snake", sfTitlebar | sfClose, NULL);
    Snake snake;
    Snake_init(&snake);
    Food food;
    Food_pick_location(&food, window);

    sfClock* clock = sfClock_create();

    while (sfRenderWindow_isOpen(window))
    {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event))
        {
            if (event.type == sfEvtClosed)
            {
                sfRenderWindow_close(window);
            }
            else if (event.type == sfEvtResized)
            {
                sfRenderWindow_setView(window, sfView_createFromRect((sfFloatRect){.width = event.size.width,
                                                                                   .height = event.size.height}));
            }
            else if (event.type == sfEvtKeyPressed)
            {
                switch (event.key.code)
                {
                case sfKeyUp:
                    Snake_dir(&snake, 0, -1);
                    break;
                case sfKeyDown:
                    Snake_dir(&snake, 0, 1);
                    break;
                case sfKeyLeft:
                    Snake_dir(&snake, -1, 0);
                    break;
                case sfKeyRight:
                    Snake_dir(&snake, 1, 0);
                    break;
                default:
                    break;
                }
            }
        }

        float delta_time = sfTime_asSeconds(sfClock_restart(clock));
        Snake_update(&snake, window, delta_time);
        if (Snake_eat(&snake, food))
        {
            Food_pick_location(&food, window);
        }

        sfRenderWindow_clear(window, (sfColor){.r = 51, .g = 51, .b = 51, .a = 255});
        Snake_draw(&snake, window);
        Food_draw(&food, window);
        sfRenderWindow_display(window);
    }

    sfClock_destroy(clock);
    sfRenderWindow_destroy(window);
    return 0;
}
