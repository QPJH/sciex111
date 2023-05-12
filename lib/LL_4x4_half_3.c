#include "LL_4x4_half_3.h"
#include "board.h"
#include "route.h"

BOARD *
LL_4x4_half_3(void)
{
    ROUTE *route, *last;
    BOARD *board;

    board = board_create(4, 4);

    route = route_create(1, 3, 1, SMALL_L);
    last = route_next(route, 0, 2, BIG_L);
    last = route_next(last, 1, 0, SMALL_L);
    last = route_next(last, 0, 1, BIG_L);
    last = route_next(last, 2, 0, SMALL_L);
    last = route_next(last, 1, 1, BIG_L);
    last = route_next(last, 3, 2, SMALL_L);
    last = route_next(last, 2, 3, BIG_L);
    last = route_next(last, 3, 1, SMALL_L);
    board_addRoute(board, route);
    return board;
}
