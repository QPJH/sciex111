#include "LL_4x4_half_2.h"
#include "board.h"
#include "route.h"

BOARD *
LL_4x4_half_2(void)
{
    ROUTE *route, *last;
    BOARD *board;

    board = board_create(4, 4);

    route = route_create(2, 2, 1, SMALL_L);
    last = route_next(route, 3, 3, BIG_L);
    last = route_next(last, 1, 2, SMALL_L);
    last = route_next(last, 0, 3, BIG_L);
    last = route_next(last, 1, 1, SMALL_L);
    last = route_next(last, 0, 0, BIG_L);
    last = route_next(last, 2, 1, SMALL_L);
    last = route_next(last, 3, 0, BIG_L);
    board_addRoute(board, route);  // 把路線放到 board1

    return board;
}
