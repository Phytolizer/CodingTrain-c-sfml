#include <SFML/Graphics/CircleShape.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/RenderTexture.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Time.h>
#include <SFML/System/Types.h>
#include <SFML/Window/Event.h>
#include <SFML/Window/Window.h>
#include <math.h>

#define C 2

int main(void)
{
    sfContextSettings contextSettings = {
        .antialiasingLevel = 8,
        .attributeFlags = sfContextCore,
        .depthBits = 24,
        .stencilBits = 8,
        .majorVersion = 3,
        .minorVersion = 3,
        .sRgbCapable = sfFalse,
    };
    sfRenderWindow* window = sfRenderWindow_create((sfVideoMode){.bitsPerPixel = 32, .width = 400, .height = 400},
                                                   "Phyllotaxis", sfTitlebar | sfClose, &contextSettings);
    sfRenderTexture* texture = sfRenderTexture_create(400, 400, sfFalse);
    sfRenderTexture_clear(texture, sfBlack);

    sfCircleShape* dot = sfCircleShape_create();
    sfCircleShape_setRadius(dot, 4);
    sfCircleShape_setOrigin(dot, (sfVector2f){4, 4});
    sfCircleShape_setFillColor(dot, sfWhite);
    unsigned int n = 0;

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

        if (sfTime_asSeconds(sfClock_getElapsedTime(clock)) > 1.0)
        {
            sfClock_restart(clock);
            double a = n * 137.5 * M_PI / 180;
            double r = C * sqrt(n);

            double x = r * cos(a) + 200;
            double y = r * sin(a) + 200;
            sfCircleShape_setPosition(dot, (sfVector2f){x, y});
            sfRenderTexture_drawCircleShape(texture, dot, NULL);
            sfRenderTexture_display(texture);
            ++n;
        }

        sfRenderWindow_clear(window, sfBlack);
        const sfTexture* rawTexture = sfRenderTexture_getTexture(texture);
        sfSprite* sprite = sfSprite_create();
        sfSprite_setTexture(sprite, rawTexture, sfTrue);
        sfRenderWindow_drawSprite(window, sprite, NULL);
        sfRenderWindow_display(window);
    }

    sfRenderWindow_destroy(window);
    return 0;
}