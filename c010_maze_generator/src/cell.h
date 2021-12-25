#pragma once

#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>
#include <toolbox/vector.h>

enum
{
    WALL_TOP,
    WALL_RIGHT,
    WALL_BOTTOM,
    WALL_LEFT,
};

typedef struct
{
    unsigned int i;
    unsigned int j;
    sfRectangleShape* background;
    sfRectangleShape* lines[4];
    bool walls[4];
    bool visited;
    bool highlight;
} Cell;

TOOLBOX_VECTOR_DECLARE(CellVec, Cell);
TOOLBOX_VECTOR_DECLARE(CellPVec, Cell*);

void Cell_init(Cell* c, unsigned int i, unsigned int j, unsigned int w);
void Cell_deinit(Cell c);
void Cell_setHighlight(Cell* c, bool highlight);
void Cell_show(Cell* c, sfRenderWindow* window);
Cell* Cell_checkNeighbors(Cell* c, sfVector2u gridSize, CellVec* grid);
void Cell_removeWalls(Cell* a, Cell* b);
