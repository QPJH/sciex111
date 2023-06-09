#include "L_6x7_End_1.h"
#include "board.h"
#include "route.h"

BOARD *L_6x7_End_1(void)
{
    ROUTE *route, *last;
    BOARD *board;

    board = board_create(7, 6);

    route = route_create(4, 0, 0,BIG_L);
    last  = route_next(route,5,2,SMALL_L);
    last  = route_next(last,4,3,BIG_L);
    last  = route_next(last,2,2,SMALL_L);
    last  = route_next(last,3,3,BIG_L);
    last  = route_next(last,2,1,SMALL_L);
    last  = route_next(last,3,0,BIG_L);
    last  = route_next(last,1,1,SMALL_L);
    last  = route_next(last,0,0,BIG_L);
    last  = route_next(last,1,2,SMALL_L);
    last  = route_next(last,0,3,BIG_L);
    last  = route_next(last,1,5,SMALL_L);
    last  = route_next(last,0,4,BIG_L);
    last  = route_next(last,2,5,SMALL_L);
    last  = route_next(last,3,4,BIG_L);
    last  = route_next(last,5,5,SMALL_L);
    last  = route_next(last,4,4,BIG_L);
    last  = route_next(last,2,3,SMALL_L);
    last  = route_next(last,3,2,BIG_L);
    last  = route_next(last,5,1,SMALL_L);
    last  = route_next(last,4,2,BIG_L);
    last  = route_next(last,5,0,SMALL_L);
    last  = route_next(last,4,1,BIG_L);
    last  = route_next(last,2,0,SMALL_L);
    last  = route_next(last,3,1,BIG_L);
    last  = route_next(last,1,0,SMALL_L);
    last  = route_next(last,0,1,BIG_L);
    last  = route_next(last,1,3,SMALL_L);
    last  = route_next(last,0,2,BIG_L);
    last  = route_next(last,1,4,SMALL_L);
    last  = route_next(last,0,5,BIG_L);
    last  = route_next(last,2,4,SMALL_L);
    last  = route_next(last,3,5,BIG_L);
    last  = route_next(last,5,4,SMALL_L);
    last  = route_next(last,4,5,BIG_L);
    last  = route_next(last,6,4,SMALL_L);
    last  = route_next(last,5,3,BIG_L);
    last  = route_next(last,6,1,SMALL_L);

    board_addRoute(board, route);  // 把路線放到 board1

    return board;
}
