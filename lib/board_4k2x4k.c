#include <stdlib.h>
#include "board_4k2x4k.h"
#include "L_4x4_half_1.h"
#include "LL_4x4_half_1.h"
#include "LL_4x6_full.h"
#include "LL_4x4_half_2.h"
#include "LL_4x4_half_3.h"


BOARD *
board_4k2x4k(int n, int m)
{
    // 4k2 x 4k
    int i, tmp;
    BOARD *tmpBoard, *board4M, *totalBoard, *headBoard, *bodyBoard1, *middleBoard, *bodyBoard2, *tailBoard;
    ROUTE *route;

    headBoard = L_4x4_half_1();
    bodyBoard1 = LL_4x4_half_1();
    middleBoard = LL_4x6_full();
    bodyBoard2 = LL_4x4_half_2();
    tailBoard = LL_4x4_half_3();

    //headBoard + bodyBoard1
    totalBoard = board_copy(headBoard);
    tmpBoard = NULL;

    for(i = 0; i < ((m - 2)/ 4 - 2); i++)
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
        board_destory(tmpBoard);
        tmpBoard = board_copy(middleBoard);
        route = board_mergeRoute(totalBoard, tmpBoard, 0, tmp = totalBoard->sizeM);
        board_destory(totalBoard);
        totalBoard = board_create(4, tmp + 6);
        board_addRoute(totalBoard, route);
    }

    for(i = 0; i < ((m - 2)/ 4 - 2); i++)
    {
        // bodyBoard2
        board_destory(tmpBoard);
        tmpBoard = board_copy(bodyBoard2);
        route = board_mergeRoute(totalBoard, tmpBoard, 0, (totalBoard->sizeM - (i + 1) * 4 - 6));
        board_destory(totalBoard);
        totalBoard = board_create(4, m);
        board_addRoute(totalBoard, route);
    }

    // tailBoard
    board_destory(tmpBoard);
    tmpBoard = board_copy(tailBoard);
    route = board_mergeRoute(totalBoard, tmpBoard, 0, 0);
    board_destory(totalBoard);
    totalBoard = board_create(4, m);
    board_addRoute(totalBoard, route);

    // full board
    board4M = board_copy(totalBoard);
    for(i = 0; i < (n / 4 - 1); i++)
    {
        board_destory(tmpBoard);
        tmpBoard = board_copy(board4M);
        route = board_mergeRoute(totalBoard, tmpBoard, totalBoard->sizeN, 0);
        board_destory(totalBoard);
        totalBoard = board_create(4 * (i + 2), m);
        board_addRoute(totalBoard, route);
    }
    board_svg(totalBoard);

    return totalBoard;
}
