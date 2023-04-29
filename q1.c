#include <stdio.h>
#include "lib/route.h"
#include "lib/board.h"

int main()
{
    BOARD *board;
    ROUTE *route, *next;

    board = board_create(10, 10);
    // board_destory(board);
    // 新路線從 (0,0) 開始
    route = route_create(0, 0, 1);
    // 加一個下一步 (1,1)
    next = route_next(route, 1, 1);
    // 加一個下一步 (2,2)
    next = route_next(next, 2, 2);
    // 加一個下一步 (3,3)
    next = route_next(next, 3, 3);

    // 印出所有步驟
    route_print(route);

    // clean up memory
    route_destory(route);

    return 0;
}
