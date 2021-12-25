#include "cell.h"
#include "toolbox/random.h"
#include "toolbox/vector.h"
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/System/Vector2.h>
#include <limits.h>

TOOLBOX_VECTOR_IMPLEMENT(CellVec, Cell, TOOLBOX_VECTOR_DESTRUCTOR(CellVec, Cell_deinit));
TOOLBOX_VECTOR_IMPLEMENT(CellPVec, Cell*, TOOLBOX_VECTOR_DESTRUCTOR_NONE(CellPVec));

static unsigned int gridIndex(unsigned int i, unsigned int j, sfVector2u gridSize);

void Cell_init(Cell* c, unsigned int i, unsigned int j, unsigned int w)
{
    c->i = i;
    c->j = j;
    c->visited = false;
    c->background = sfRectangleShape_create();
    sfRectangleShape_setPosition(c->background, (sfVector2f){i * w, j * w});
    sfRectangleShape_setSize(c->background, (sfVector2f){w, w});
    sfRectangleShape_setFillColor(c->background, sfColor_fromRGBA(255, 0, 255, 100));
    for (size_t i = 0; i < 4; ++i)
    {
        c->lines[i] = sfRectangleShape_create();
        sfRectangleShape_setFillColor(c->lines[i], sfWhite);
        c->walls[i] = true;
    }
    sfRectangleShape_setPosition(c->lines[WALL_TOP], (sfVector2f){i * w, j * w});
    sfRectangleShape_setSize(c->lines[WALL_TOP], (sfVector2f){w, 1});
    sfRectangleShape_setPosition(c->lines[WALL_RIGHT], (sfVector2f){(i + 1) * w - 1, j * w});
    sfRectangleShape_setSize(c->lines[WALL_RIGHT], (sfVector2f){1, w});
    sfRectangleShape_setPosition(c->lines[WALL_BOTTOM], (sfVector2f){i * w, (j + 1) * w - 1});
    sfRectangleShape_setSize(c->lines[WALL_BOTTOM], (sfVector2f){w, 1});
    sfRectangleShape_setPosition(c->lines[WALL_LEFT], (sfVector2f){i * w, j * w});
    sfRectangleShape_setSize(c->lines[WALL_LEFT], (sfVector2f){1, w});
}

void Cell_deinit(Cell c)
{
    sfRectangleShape_destroy(c.background);
    for (size_t i = 0; i < 4; ++i)
    {
        sfRectangleShape_destroy(c.lines[i]);
    }
}

void Cell_setHighlight(Cell* c, bool highlight)
{
    if (highlight)
    {
        sfRectangleShape_setFillColor(c->background, sfColor_fromRGBA(0, 255, 0, 100));
    }
    else
    {
        sfRectangleShape_setFillColor(c->background, sfColor_fromRGBA(255, 0, 255, 100));
    }
}

void Cell_show(Cell* c, sfRenderWindow* window)
{
    if (c->visited)
    {
        sfRenderWindow_drawRectangleShape(window, c->background, NULL);
    }
    for (size_t i = 0; i < 4; ++i)
    {
        if (c->walls[i])
        {
            sfRenderWindow_drawRectangleShape(window, c->lines[i], NULL);
        }
    }
}

Cell* Cell_checkNeighbors(Cell* c, sfVector2u gridSize, CellVec* grid)
{
    unsigned int indices[4] = {
        [WALL_TOP] = gridIndex(c->i, c->j - 1, gridSize),
        [WALL_RIGHT] = gridIndex(c->i + 1, c->j, gridSize),
        [WALL_BOTTOM] = gridIndex(c->i, c->j + 1, gridSize),
        [WALL_LEFT] = gridIndex(c->i - 1, c->j, gridSize),
    };

    Cell* neighbors[4] = {0};
    size_t nneighbors = 0;

    for (size_t i = 0; i < 4; ++i)
    {
        if (indices[i] < grid->length && !grid->data[indices[i]].visited)
        {
            neighbors[nneighbors++] = &grid->data[indices[i]];
        }
    }

    if (nneighbors > 0)
    {
        size_t r = toolbox_random_int_range(0, nneighbors);
        return neighbors[r];
    }
    return NULL;
}

void Cell_removeWalls(Cell* a, Cell* b)
{
    int dx = (int)a->i - (int)b->i;
    int dy = (int)a->j - (int)b->j;

    if (dx == 1)
    {
        a->walls[WALL_LEFT] = false;
        b->walls[WALL_RIGHT] = false;
    }
    else if (dx == -1)
    {
        a->walls[WALL_RIGHT] = false;
        b->walls[WALL_LEFT] = false;
    }

    if (dy == 1)
    {
        a->walls[WALL_TOP] = false;
        b->walls[WALL_BOTTOM] = false;
    }
    else if (dy == -1)
    {
        a->walls[WALL_BOTTOM] = false;
        b->walls[WALL_TOP] = false;
    }
}

unsigned int gridIndex(unsigned int i, unsigned int j, sfVector2u gridSize)
{
    if (i == UINT_MAX || j == UINT_MAX || i >= gridSize.x || j >= gridSize.y)
    {
        return UINT_MAX;
    }
    return i + j * gridSize.x;
}
