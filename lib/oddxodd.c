#include <stdio.h>
#include "oddxodd.h"
#include "board_4kx4k.h"
#include "board_4kx4k2.h"
#include "board_4k2x4k.h"
#include "board_4k2x4k2.h"
#include "L_3x3_start.h"

// create odd x odd
BOARD *oddxodd(int n, int m)
{
    // odd x odd
    int i, tmp;
    BOARD *tmpBoard, *totalBoard, *headBoard, *bodyBoard1, *bodyBoard2, *bodyBoard3 ,*bodyBoard4;
    ROUTE *route;

    headBoard = L_3x3_start();
    //bodyBoard1 = board_4kx4k();
    bodyBoard2 = board_4kx4k2();
    //bodyBoard3 = board_4k2x4k();
    //bodyBoard4 = board_4k2x4k2();
    tmpBoard = NULL;

    //headBoard + bodyBoard1


    return totalBoard;
}
