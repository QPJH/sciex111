#include "board.h"
#include "route.h"

BOARD *
L_3x6_half_1(void)
{
    ROUTE *route, *last;
    BOARD *board;

    board = board_create(3, 6);

    route = route_create(0, 0, 0, BIG_L);
    last = route_next(route, 1, 2, SMALL_L);
    last = route_next(last, 0, 3, BIG_L);
    last = route_next(last, 1, 1, SMALL_L);
    last = route_next(last, 0, 2, BIG_L);
    last = route_next(last, 1, 0, SMALL_L);
    last = route_next(last, 0, 1, BIG_L);
    last = route_next(last, 2, 2, SMALL_L);
    last = route_next(last, 1, 3, BIG_L);
    last = route_next(last, 2, 5, SMALL_L);
    board_addRoute(board, route);
    return board;
}
