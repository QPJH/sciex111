#include "LL_4x4_half_2.h"
#include "board.h"
#include "route.h"

BOARD *
LL_4x4_half_2(void)
{
    ROUTE *route, *last;
    BOARD *board;

    board = board_create(4, 4);

    route = route_create(3, 3, 1, SMALL_L);
    last = route_next(route, 2, 2, BIG_L);
    last = route_next(last, 0, 3, SMALL_L);
    last = route_next(last, 1, 2, BIG_L);
    last = route_next(last, 0, 0, SMALL_L);
    last = route_next(last, 1, 1, BIG_L);
    last = route_next(last, 3, 0, SMALL_L);
    last = route_next(last, 2, 1, BIG_L);
    board_addRoute(board, route);  // 把路線放到 board1

    return board;
}
