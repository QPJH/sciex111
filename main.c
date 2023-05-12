#include <stdio.h>
#include "lib/route.h"
#include "lib/board.h"
#include "lib/board_4kx4k.h"

int main_2()
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

    if(m % 4 == 0 && n % 4 == 0)
    {
        BOARD *totalBoard;

        totalBoard = board_4kx4k(n, m);

        board_svg(totalBoard);
    }

    return 0;
}
