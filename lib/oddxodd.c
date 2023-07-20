#include <stdio.h>
#include "board.h"
#include "route.h"
#include "board_4kx4k.h"
#include "board_4kx4k2.h"
#include "board_4k2x4k.h"
#include "board_4k2x4k2.h"
#include "L_3x3_start.h"

BOARD *oddxodd(int n,int m)
{
    BOARD *headBoard, *evenBoard, *totalboard;
    ROUTE *route;

    totalboard = board_create(n, m);
    headBoard = L_3x3_start();
    if((m - 1) % 4 == 0 && (n - 1) % 4 == 0)// 4k x 4k
    {
        evenBoard = board_4kx4k(n - 1, m - 1);
    }

    if((m - 1) % 4 == 0 && (n - 1) % 4 == 2)// 4k x 4k2
    {
        evenBoard = board_4kx4k2(n - 1, m - 1);
    }

    if((m - 1) % 4 == 2 && (n - 1) % 4 == 0)// 4k2 x 4k
    {
        evenBoard = board_4k2x4k(n - 1, m - 1);
    }

    if((m - 1) % 4 == 2 && (n - 1) % 4 == 2)// 4k2 x 4k2
    {
        evenBoard = board_4k2x4k2(n - 1, m - 1);
    }
    route = board_mergeRouteFull(headBoard, evenBoard, 1, 1);
    board_addRoute(totalboard, route);

    return totalboard;
}
