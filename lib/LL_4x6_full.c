#include "LL_4x6_full.h"
#include "board.h"
#include "route.h"

BOARD *
LL_4x6_full(void)
{
    ROUTE *route, *last;
    BOARD *board;

    board = board_create(4, 6);

    route = route_create(2, 0, 1, SMALL_L);
    last = route_next(route, 3, 1, BIG_L);
    last = route_next(last, 2, 3, SMALL_L);
    last = route_next(last, 3, 2, BIG_L);
    last = route_next(last, 2, 4, SMALL_L);
    last = route_next(last, 3, 5, BIG_L);
    last = route_next(last, 1, 4, SMALL_L);
    last = route_next(last, 0, 5, BIG_L);
    last = route_next(last, 1, 3, SMALL_L);
    last = route_next(last, 0, 2, BIG_L);
    last = route_next(last, 1, 0, SMALL_L);
    last = route_next(last, 0, 1, BIG_L);
    last = route_next(last, 2, 2, SMALL_L);
    last = route_next(last, 3, 3, BIG_L);
    last = route_next(last, 2, 5, SMALL_L);
    last = route_next(last, 3, 4, BIG_L);
    last = route_next(last, 1, 5, SMALL_L);
    last = route_next(last, 0, 4, BIG_L);
    last = route_next(last, 1, 2, SMALL_L);
    last = route_next(last, 0, 3, BIG_L);
    last = route_next(last, 1, 1, SMALL_L);
    last = route_next(last, 0, 0, BIG_L);
    last = route_next(last, 2, 1, SMALL_L);
    last = route_next(last, 3, 0, BIG_L);


    board_addRoute(board, route);  // 把路線放到 board1

    return board;
}
