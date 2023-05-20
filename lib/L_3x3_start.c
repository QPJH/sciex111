#include "L_3x3_start.h"
#include "board.h"
#include "route.h"

BOARD *
L_3x3_start(void)
{
    ROUTE *route, *last;
    BOARD *board;

    board = board_create(3, 3);

    route = route_create(0, 2, 0, BIG_L);
    last = route_next(route, 1, 0, SMALL_L);
    last = route_next(last, 0, 1, BIG_L);
    last = route_next(last, 2, 0, SMALL_L);


    board_addRoute(board, route);  // 把路線放到 board1

    return board;
}
