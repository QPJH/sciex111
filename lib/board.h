#ifndef __BOARD_H__
#define __BOARD_H__

#include "route.h"

// BOARD
typedef struct BOARD BOARD;

struct BOARD
{
    // board size
    int sizeN;
    int sizeM;
    // for (x, y), n for index of grid[n], n = x + y*(sizeN)

    ROUTE *route;     // the route at with the board
    ROUTE *(*grids);  // grids of routes, grids[n] stores a route for (x, y)
};

// destory the board
void board_destory(BOARD *board);

// create a board with size (N, M)
BOARD * board_create(unsigned sizeN, unsigned sizeM);

// get board length
unsigned board_length(BOARD *board);
#endif
