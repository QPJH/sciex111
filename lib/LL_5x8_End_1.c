#include "LL_4x4_half_3.h"
#include "board.h"
#include "route.h"

BOARD *
LL_5x8_End_1(void)
{
    ROUTE *route, *last;
    BOARD *board;

    board = board_create(5, 8);

    route = route_create(4, 6, 1, SMALL_L);
    last = route_next(route, 3, 7, BIG_L);
    last = route_next(last, 1, 6, SMALL_L);
    last = route_next(last, 0, 7, BIG_L);
    last = route_next(last, 2, 6, SMALL_L);
    last = route_next(last, 1, 5, BIG_L);
    last = route_next(last, 3, 4, SMALL_L);
    last = route_next(last, 2, 5, BIG_L);
    last = route_next(last, 0, 4, SMALL_L);
    last = route_next(last, 1, 3, BIG_L);
    last = route_next(last, 0, 1, SMALL_L);
    last = route_next(last, 1, 0, BIG_L);
    last = route_next(last, 0, 2, SMALL_L);
    last = route_next(last, 1, 1, BIG_L);
    last = route_next(last, 2, 3, SMALL_L);
    last = route_next(last, 3, 2, BIG_L);
    last = route_next(last, 2, 0, SMALL_L);
    last = route_next(last, 3, 1, BIG_L);
    last = route_next(last, 4, 3, SMALL_L);
    board_addRoute(board, route);
    return board;
}
