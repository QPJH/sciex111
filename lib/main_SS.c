#include <stdio.h>
#include "adam.h"
#include "allen.h"
#include "irene.h"
#include "route.h"
#include "board.h"

int main()
{
    int m = 0, n = 0,r;
    while(m * n == 0)
    {
        printf("BS(1) or SS(2)?");
        scanf("%d",&r);
        if(r > 2 || r <= 0)
        {
            printf("Error \n");
            r=0;
        }
        if (r == 2 || r == 1)
        {
            while(m * n == 0)
            {
                printf("m = ? ");
                scanf("%d",&m);
                printf("n = ? ");
                scanf("%d",&n);

                if(m == 1 && n == 1)
                {
                    printf("\n0\n");
                    return 0;
                }

                if(m <= 0 || n <= 0)
                {
                    printf("Error \n");
                    m = n = 0;
                }
            }
        }


    }

    if (r == 1)
    {
        if(m % 4 == 0 && n % 4 == 0)// 4k x 4k
        {
            BOARD *totalBoard;

            totalBoard = board_4kx4k(n, m);

            board_print(totalBoard);

            board_svg(totalBoard);

            return 0;
        }

        if(m % 4 == 0 && n % 4 == 2)// 4k x 4k2
        {
            BOARD *totalBoard;

            totalBoard = board_4kx4k2(n, m);

            board_print(totalBoard);

            board_svg(totalBoard);

            return 0;
        }

        if(m % 4 == 2 && n % 4 == 0)// 4k2 x 4k
        {
            BOARD *totalBoard;

            totalBoard = board_4k2x4k(n, m);

            board_print(totalBoard);

            board_svg(totalBoard);

            return 0;
        }

        if(m % 4 == 2 && n % 4 == 2)// 4k2 x 4k2
        {
            BOARD *totalBoard;

            totalBoard = board_4k2x4k2(n, m);

            board_print(totalBoard);

            board_svg(totalBoard);

            return 0;
        }
    }

    /*
     if(m % 4 == 0 && n % 4 == 3)// 4k x 4k3
     {
         BOARD *totalBoard;

         totalBoard = board_4kx4k3(n, m);

         board_print(totalBoard);

         board_svg(totalBoard);

         return 0;
     }
     */

    // DFS

    if(r == 1)
    {
        BOARD *totalBoard;
        ROUTE *route, *maxRoute;

        totalBoard = board_create(n, m);
        route = route_create(0, 0, 0, BIG_L);
        board_addRoute(totalBoard, route);

        maxRoute = adam_dfsRoute(totalBoard);

        board_destory(totalBoard);

        totalBoard = board_create(n, m);

        board_addRoute(totalBoard, maxRoute);

        board_svg(totalBoard);
        board_print(totalBoard);

        return 0;
    }
    else if(r==2)
    {
        BOARD *totalBoard;
        ROUTE *route, *maxRoute;

        totalBoard = board_create(n, m);
        if (m % 2 != 0 && n % 2 != 0)
        {
            route = route_create(1, 0, 0, SMALL_L);
        }
        else
        {
            route = route_create(0, 0, 0, SMALL_L);
        }
        board_addRoute(totalBoard, route);

        maxRoute = allen_dfsRoute(totalBoard);

        board_destory(totalBoard);

        totalBoard = board_create(n, m);

        board_addRoute(totalBoard, maxRoute);

        board_svg(totalBoard);
        board_print(totalBoard);
    }
}
