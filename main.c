#include <stdio.h>
#include "lib/route.h"
#include "lib/board.h"
#include "lib/board_4kx4k.h"
#include "lib/board_4k2x4k.h"
#include "lib/board_4kx4k2.h"
#include "lib/board_4k2x4k2.h"

int main()
{
    int m = 0, n = 0;
    while(m * n == 0)
    {
        // 強迫m, n要大於0
        printf("請輸入m(高)：");
        scanf("%d",&m);
        printf("請輸入n(寬)：");
        scanf("%d",&n);

        if(m <= 0 || n <= 0)
        {
            printf("(m, n)需為正數\n");
            m = n = 0;
        }
    }

    if(m % 4 == 0 && n % 4 == 0)// 4k x 4k
    {
        BOARD *totalBoard;

        totalBoard = board_4kx4k(m, n);

        board_print(totalBoard);

        board_svg(totalBoard);
    }

    if(m % 4 == 0 && n % 4 == 2)// 4k x 4k2
    {
        BOARD *totalBoard;

        //totalBoard = board_4kx4k2(m, n);

        board_print(totalBoard);

        board_svg(totalBoard);
    }

    if(m % 4 == 2 && n % 4 == 0)// 4k2 x 4k
    {
        BOARD *totalBoard;

        //totalBoard = board_4k2x4k(m, n);

        board_print(totalBoard);

        board_svg(totalBoard);
    }

    if(m % 4 == 2 && n % 4 == 2)// 4k2 x 4k2
    {
        BOARD *totalBoard;

        //totalBoard = board_4k2x4k2(m, n);

        board_print(totalBoard);

        board_svg(totalBoard);
    }

    /*
    if(m % 4 == 2 && n % 4 == 1)// (4k+2) x (4k+1)
    {
        BOARD *totalboard;

        totalboard = board_4k2x4k1(m, n);

        board_print(totalboard);
    }
    */

    return 0;
}
