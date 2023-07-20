#include <stdio.h>
#include "board_4k2x4k.h"
#include "LL_5x8_End_1.h"
#include "L_4x4_half_1.h"
#include "LL_4x4_half_1.h"
#include "LL_4x6_full.h"
#include "LL_4x4_half_2.h"
#include "LL_4x4_half_3.h"
#include "L_2x4_full.h"
#include "adam.h"

// create 4k x 4k2
BOARD *board_4k2x4k1(int n, int m)
{
    // 4k x 4k2
    int i,tmp;
    BOARD *firstBoard, *headBoard, *bodyBoard1, *bodyBoard2, *middleBoard, *tailBoard, *tailBoard2, *totalBoard, *tmpBoard;
    ROUTE *route;

    firstBoard = board_4k2x4k(n - 5, m);

    headBoard = L_4x4_half_1();
    bodyBoard1 = LL_4x4_half_1();
    middleBoard = LL_4x6_full();
    bodyBoard2 = LL_4x4_half_2();
    tailBoard = LL_4x4_half_3();
    tailBoard2 = LL_5x8_End_1();
    tmpBoard = NULL;

    //headBoard + bodyBoard1
    totalBoard = board_copy(headBoard);

    for(i = 0; i < ((m-2) / 4 - 2); i++)
    {
        // bodyBoard1
        tmpBoard = board_copy(bodyBoard1);
        route = board_mergeRoute(totalBoard, tmpBoard, 0, tmp = totalBoard->sizeM);
        board_destory(totalBoard);
        totalBoard = board_create(4, tmp + 4);
        board_addRoute(totalBoard, route);
    }

    if(m > 6)
    {
        // middleBoard
        if (tmpBoard) {
            board_destory(tmpBoard);
        }
        tmpBoard = board_copy(middleBoard);
        route = board_mergeRoute(totalBoard, tmpBoard, 0, tmp = totalBoard->sizeM);
        board_destory(totalBoard);
        totalBoard = board_create(4, tmp + 6);
        board_addRoute(totalBoard, route);
    }

    for(i = 0; i < ((m-2) / 4 - 3); i++)
    {
        // bodyBoard2
        board_destory(tmpBoard);
        tmpBoard = board_copy(bodyBoard2);
        route = board_mergeRoute(totalBoard, tmpBoard, 0, (totalBoard->sizeM - (i + 1) * 4 - 6));
        board_destory(totalBoard);
        totalBoard = board_create(4, m);
        board_addRoute(totalBoard, route);
    }

    // tailBoard2
    if(tmpBoard) {
        board_destory(tmpBoard);
    }
    tmpBoard = board_copy(tailBoard2);
    route = board_mergeRoute(totalBoard, tmpBoard, 0, 0);
    board_destory(totalBoard);
    totalBoard = board_create(5, m);
    board_addRoute(totalBoard, route);

    // fullboard
    board_destory(tmpBoard);
    tmpBoard = board_copy(totalBoard);
    route = board_mergeRouteFull(firstBoard, tmpBoard, firstBoard->sizeN, 0);
    board_destory(totalBoard);
    totalBoard = board_create(n, m);
    board_addRoute(totalBoard, route);

    return totalBoard;
}
