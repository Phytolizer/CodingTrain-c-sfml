#include "drop.h"
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Time.h>
#include <SFML/System/Types.h>
#include <SFML/Window/Event.h>
#include <SFML/Window/VideoMode.h>
#include <SFML/Window/Window.h>
#include <stdio.h>

int main(void)
{
    sfContextSettings settings = {
        .antialiasingLevel = 8,
        .attributeFlags = sfContextDefault,
        .depthBits = 24,
        .stencilBits = 8,
        .majorVersion = 3,
        .minorVersion = 3,
        .sRgbCapable = sfFalse,
    };
    sfRenderWindow* window = sfRenderWindow_create((sfVideoMode){.bitsPerPixel = 32, .width = 640, .height = 360},
                                                   "Purple Rain", sfTitlebar | sfClose, &settings);

    DropVector drops;
    DropVector_init(&drops);
    for (size_t i = 0; i < 500; ++i)
    {
        Drop drop;
        Drop_init(&drop, window);
        DropVector_push(&drops, drop);
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
            default:
                break;
            }
        }

        float delta_time = sfTime_asSeconds(sfClock_restart(clock));
        for (size_t i = 0; i < drops.length; ++i)
        {
            Drop_fall(&drops.data[i], window, delta_time);
        }

        sfRenderWindow_clear(window, sfColor_fromRGB(230, 230, 250));
        for (size_t i = 0; i < drops.length; ++i)
        {
            Drop_show(&drops.data[i], window);
        }
        sfRenderWindow_display(window);
    }

    DropVector_deinit(&drops);

    sfRenderWindow_destroy(window);
}
