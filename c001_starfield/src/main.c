#include "star.h"
#include <SFML/Config.h>
#include <SFML/Graphics/CircleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Graphics/View.h>
#include <SFML/System/Clock.h>
#include <SFML/Window/Event.h>
#include <SFML/Window/Window.h>

int main(void)
{
    sfContextSettings windowSettings = {
        .antialiasingLevel = 8,
        .majorVersion = 3,
        .minorVersion = 3,
        .attributeFlags = sfContextDefault,
        .depthBits = 24,
        .stencilBits = 8,
        .sRgbCapable = sfFalse,
    };
    sfRenderWindow* window = sfRenderWindow_create((sfVideoMode){.bitsPerPixel = 32, .width = 800, .height = 800},
                                                   "Starfield", sfDefaultStyle, &windowSettings);

    StarVector stars;
    StarVector_init(&stars);
    for (size_t i = 0; i < 500; i++)
    {
        Star star;
        Star_init(&star, window);
        StarVector_push(&stars, star);
    }

    sfClock* clock = sfClock_create();
    while (sfRenderWindow_isOpen(window))
    {
        sfEvent event;
        while (sfWindow_pollEvent((sfWindow*)window, &event))
        {
            if (event.type == sfEvtClosed)
            {
                sfRenderWindow_close(window);
            }
            if (event.type == sfEvtResized)
            {
                sfRenderWindow_setView(window, sfView_createFromRect((sfFloatRect){.width = event.size.width,
                                                                                   .height = event.size.height}));
            }
        }
        float delta_time = sfTime_asSeconds(sfClock_getElapsedTime(clock));
        sfClock_restart(clock);
        for (size_t i = 0; i < stars.length; ++i)
        {
            Star_update(&stars.data[i], window, delta_time);
        }

        sfRenderWindow_clear(window, sfBlack);
        for (size_t i = 0; i < stars.length; ++i)
        {
            Star_draw(&stars.data[i], window);
        }
        sfRenderWindow_display(window);
    }

    sfClock_destroy(clock);
    StarVector_deinit(&stars);
    sfRenderWindow_destroy(window);
    return 0;
}
