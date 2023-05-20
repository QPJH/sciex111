#include "board_4K2x4K2.h"
#include "L_4x4_half_1.h"
#include "LL_4x4_half_1.h"
#include "LL_4x4_full_1.h"
#include "LL_4x4_half_2.h"
#include "L_6x6_full.h"
#include "LL_4x6_full.h"
#include "L_2x4_full.h"
#include "board_4kx4k2.h"

BOARD *board_4k2x4k2(int m,int n)
{
    int i,tmp,flag=0;
    BOARD *tmpBoard, *board4M, *totalBoard, *headBoard, *bodyBoard1,*middleBoard1, *middleBoard2,*middleBoard3, *bodyBoard2,*tailBoard1, *tailBoard2;
    ROUTE *route;
    headBoard=L_4x4_half_1();
    bodyBoard1=LL_4x4_half_1();
    middleBoard1=LL_4x4_full_1();
    middleBoard2=LL_4x6_full();
    middleBoard3=L_6x6_full();
    bodyBoard2=LL_4x4_half_2();
    tailBoard1=LL_4x4_half_3();
    tailBoard2=L_2x4_full();

    totalBoard = board_copy(headBoard);


    for(i = 0; i < ((m - 6)/ 4 - 1); i++)
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
        tmpBoard = board_copy(middleBoard2);
        route = board_mergeRoute(totalBoard, tmpBoard, 0, tmp = totalBoard->sizeM);
        board_destory(totalBoard);
        totalBoard = board_create(4, tmp + 6);
        board_addRoute(totalBoard, route);
    }

    for(i = 0; i < ((m - 6) / 4 - 1); i++)
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
    tmpBoard = board_copy(tailBoard1);
    route = board_mergeRoute(totalBoard, tmpBoard, 0, 0);
    board_destory(totalBoard);
    totalBoard = board_create(4, m);
    board_addRoute(totalBoard, route);

    // full board
    board4M = board_copy(totalBoard);
    for(i = 0; i < ((n - 2)/ 4 - 1); i++)
    {
        board_destory(tmpBoard);
        tmpBoard = board_copy(board4M);
        route = board_mergeRoute(totalBoard, tmpBoard, totalBoard->sizeN, 0);
        board_destory(totalBoard);
        totalBoard = board_create(4 * (i + 2), m);
        board_addRoute(totalBoard, route);
    }

    board_destory(tmpBoard);
    tmpBoard=board_4kx4k2(6,m-6);
    route = board_mergeRoute(totalBoard, tmpBoard, n-6, 0);
    board_destory(totalBoard);
    totalBoard = board_create(n, m);
    board_addRoute(totalBoard, route);

    route = board_mergeRoute(totalBoard, middleBoard3, n-6, m-6);
    board_destory(totalBoard);
    totalBoard = board_create(n, m);
    board_addRoute(totalBoard, route);

    return totalBoard;
}
