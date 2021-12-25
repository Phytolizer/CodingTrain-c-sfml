#include "c005_space_invaders/src/flower.h"
#include "ship.h"
#include "toolbox/random.h"
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Time.h>
#include <SFML/Window/Event.h>
#include <SFML/Window/VideoMode.h>
#include <SFML/Window/Window.h>

int main(void)
{
    sfContextSettings contextSettings = {
        .antialiasingLevel = 8,
        .attributeFlags = sfContextDefault,
        .depthBits = 24,
        .stencilBits = 8,
        .majorVersion = 3,
        .minorVersion = 3,
        .sRgbCapable = sfFalse,
    };
    sfRenderWindow* window = sfRenderWindow_create((sfVideoMode){.bitsPerPixel = 32, .width = 600, .height = 400},
                                                   "Space Invaders", sfTitlebar | sfClose, &contextSettings);
    sfVector2u windowSize = sfRenderWindow_getSize(window);

    Ship ship;
    Ship_init(&ship, window);

    FlowerVector flowers;
    FlowerVector_init(&flowers);

    for (size_t i = 0; i < 6; ++i)
    {
        Flower f;
        Flower_init(&f, (sfVector2f){
                            .x = i * 80 + 80,
                            .y = 60,
                        });
        FlowerVector_push(&flowers, f);
    }

    sfClock* clock = sfClock_create();

    while (sfRenderWindow_isOpen(window))
    {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event))
        {
            switch (event.type)
            {
            case sfEvtClosed:
                sfRenderWindow_close(window);
                break;
            case sfEvtKeyPressed:
                switch (event.key.code)
                {
                case sfKeyLeft:
                    Ship_move(&ship, -1);
                    break;
                case sfKeyRight:
                    Ship_move(&ship, 1);
                    break;
                default:
                    break;
                }
                break;
            case sfEvtKeyReleased:
                switch (event.key.code)
                {
                case sfKeyLeft:
                    Ship_move(&ship, 1);
                    break;
                case sfKeyRight:
                    Ship_move(&ship, -1);
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }

        float delta_time = sfTime_asSeconds(sfClock_restart(clock));
        Ship_update(&ship, window, delta_time);
        for (size_t i = 0; i < flowers.length; i++)
        {
            Flower_update(&flowers.data[i], window, delta_time);
        }

        sfRenderWindow_clear(window, sfColor_fromRGB(51, 51, 51));
        Ship_show(&ship, window);
        for (size_t i = 0; i < flowers.length; i++)
        {
            Flower_show(&flowers.data[i], window);
        }
        sfRenderWindow_display(window);
    }

    Ship_deinit(&ship);
    sfRenderWindow_destroy(window);
    return 0;
}
