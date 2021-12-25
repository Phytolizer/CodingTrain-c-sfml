#include "cell.h"
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Clock.h>
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
    sfRenderWindow* window = sfRenderWindow_create((sfVideoMode){.bitsPerPixel = 32, .width = 400, .height = 400},
                                                   "Maze Generator", sfTitlebar | sfClose, &contextSettings);
    sfVector2u windowSize = sfRenderWindow_getSize(window);
    const unsigned int w = 40;
    sfVector2u gridSize = {
        .x = windowSize.x / w,
        .y = windowSize.y / w,
    };
    sfClock* clock = sfClock_create();

    CellVec grid;
    CellVec_init(&grid);

    for (unsigned int j = 0; j < gridSize.y; ++j)
    {
        for (unsigned int i = 0; i < gridSize.x; ++i)
        {
            Cell c;
            Cell_init(&c, i, j, w);
            CellVec_push(&grid, c);
        }
    }

    Cell* current = &grid.data[0];
    Cell_setHighlight(current, true);

    CellPVec stack;
    CellPVec_init(&stack);

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

        if (sfTime_asSeconds(sfClock_getElapsedTime(clock)) > 1.0 / 5.0)
        {
            sfClock_restart(clock);
            current->visited = true;
            Cell* next = Cell_checkNeighbors(current, gridSize, &grid);
            if (next != NULL)
            {
                next->visited = true;
                CellPVec_push(&stack, current);
                Cell_removeWalls(current, next);
                Cell_setHighlight(current, false);
                Cell_setHighlight(next, true);
                current = next;
            }
            else if (stack.length > 0)
            {
                Cell_setHighlight(current, false);
                current = CellPVec_pop(&stack);
                Cell_setHighlight(current, true);
            }
        }

        sfRenderWindow_clear(window, sfColor_fromRGB(51, 51, 51));
        for (size_t i = 0; i < grid.length; ++i)
        {
            Cell_show(&grid.data[i], window);
        }
        sfRenderWindow_display(window);
    }

    CellVec_deinit(&grid);
    sfClock_destroy(clock);
    sfRenderWindow_destroy(window);
}
