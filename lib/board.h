#ifndef __BOARD_H__
#define __BOARD_H__

#include "route.h"

#define BOARD_SVG_SCALE 25

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

// copy the board
BOARD *board_copy(BOARD *board);

// destory the board
void board_destory(BOARD *board);

// create a board with size (N, M)
BOARD * board_create(unsigned sizeN, unsigned sizeM);

// get board length
unsigned board_length(BOARD *board);

// print the board
void board_print(BOARD *board);

// svg board image
void board_svg(BOARD *board);

// add a route to the board
void board_addRoute(BOARD *board, ROUTE *route);

// get (x, y) grids index of the board
int board_XY2Index(BOARD *board, unsigned x, unsigned y);

// merge board and return route
ROUTE *board_mergeRoute(BOARD *bFrom, BOARD *bTo, unsigned x, unsigned y);

#endif
