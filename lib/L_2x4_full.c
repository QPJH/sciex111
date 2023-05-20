#include "L_2x4_full.h"
#include "board.h"
#include "route.h"

BOARD *
L_2x4_full(void)
{
    ROUTE *route, *last;
    BOARD *board;

    board = board_create(2, 4);

    route = route_create(0, 0, 0, BIG_L);
    last = route_next(route, 1, 2, SMALL_L);
    last = route_next(last, 0, 3, BIG_L);
    last = route_next(last, 1, 1, SMALL_L);
    last = route_next(last, 0, 2, BIG_L);
    last = route_next(last, 1, 0, SMALL_L);
    last = route_next(last, 0, 1, BIG_L);
    last = route_next(last, 1, 3, SMALL_L);

    board_addRoute(board, route);  // 把路線放到 board1

    return board;
}
