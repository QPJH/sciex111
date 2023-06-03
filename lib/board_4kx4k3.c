#include <stdio.h>
#include "board_4kx4k3.h"
#include "board_4kx4k.h"
#include "L_3x6_half_1.h"
#include "L_2x4_full.h"

BOARD *
board_4kx4k3(int n,int m)
{
    int i;
    BOARD *firstBoard, *bodyBoard, *tailBoard, *totalBoard;
    ROUTE *route;

    firstBoard = board_4kx4k(n - 3, m);
    bodyBoard = L_3x6_half_1();
    tailBoard = L_2x4_full();

    route = board_mergeRoute(firstBoard, bodyBoard,  (n - 3), 0);

    for (i = 0;i < (m / 4) - 1;i++)
    {
        route = board_mergeRoute(firstBoard, tailBoard, (n - 3), ((i + 1) * 4));
        board_destory(tailBoard);
        tailBoard = L_2x4_full();
    }

    totalBoard = board_create(n, m);

    board_addRoute(totalBoard, route);

    // board_print(totalBoard);

    return totalBoard;
}
