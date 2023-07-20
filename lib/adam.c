#include <stdio.h>
#include "route.h"
#include "board.h"
#include "adam.h"
#include "allen.h"

int maxLength = 0;
ROUTE *maxRoute = NULL;
ROUTE *last = NULL;
int v = 0;

ROUTE *
adam_dfsRoute(BOARD *board)
{
    adam_dfs2(board);
    printf("V = %d\n", v);
    return maxRoute;
}

BOARD *
adam_dfs(BOARD *board)
{
    unsigned length, i, used = 0;
    int x, y;
    BOARD *b;
    ROUTE *r, *rLast;

    if(!board->route)
    {
        return board;
    }

    length = board_length(board);

    b = board_copy(board);

    rLast = route_last(b->route);
    for(i = 0; i < length; i++)
    {
        r = rLast;

        if( b->grids[i] )
        {
            used ++;
            continue;
        }

        x = i % board->sizeN;
        y = i / board->sizeN;

        if(r->nextMove == BIG_L)
        {
            if (
                (x == (r->x - 1) &&  y == (r->y - 2)) ||
                (x == (r->x + 1) &&  y == (r->y - 2)) ||
                (x == (r->x - 2) &&  y == (r->y - 1)) ||
                (x == (r->x + 2) &&  y == (r->y - 1)) ||
                (x == (r->x - 2) &&  y == (r->y + 1)) ||
                (x == (r->x + 2) &&  y == (r->y + 1)) ||
                (x == (r->x - 1) &&  y == (r->y + 2)) ||
                (x == (r->x + 1) &&  y == (r->y + 2))
            )
            {
                r = route_next(r, x, y, SMALL_L);
                b->grids[i] = r;
                adam_dfs(b);
                b->grids[i] = NULL;
                route_destory(r);
            }
        }
        else        // SMALL_L
        {
            if (
                (x == (r->x - 1) &&  y == (r->y - 1)) ||
                (x == (r->x + 1) &&  y == (r->y - 1)) ||
                (x == (r->x - 1) &&  y == (r->y + 1)) ||
                (x == (r->x + 1) &&  y == (r->y + 1))
            )
            {
                r = route_next(r, x, y, BIG_L);
                b->grids[i] = r;
                adam_dfs(b);
                b->grids[i] = NULL;
                route_destory(r);
            }
        }

    }

    // no next move;
    if ( rLast->stepNo > maxLength )
    {
        if( (maxRoute))
        {
            route_destory(maxRoute);
        }
        maxRoute = route_copy(b->route);
        maxLength = rLast->stepNo;
    }

    if(length == used)
    {
        board_print(board);
    }

    route_destory(b->route);
    board_destory(b);

    return board;
}

BOARD *
adam_dfs2(BOARD *board)
{
    unsigned length, i, j, used = 0;
    int x, y;
    ROUTE *r, *r2;

    v ++;
    if(!board->route)
    {
        return board;
    }

    length = board_length(board);

    if (!last)
    {
        last = route_last(board->route);
    }

    for(i = 0; i < length; i++)
    {
        r = last;

        if( board->grids[i] )
        {
            continue;
        }

        x = i % board->sizeN;
        y = i / board->sizeN;

        // BIG_L
        if (
            (x == (r->x - 1) &&  y == (r->y - 2)) ||
            (x == (r->x + 1) &&  y == (r->y - 2)) ||
            (x == (r->x - 2) &&  y == (r->y - 1)) ||
            (x == (r->x + 2) &&  y == (r->y - 1)) ||
            (x == (r->x - 2) &&  y == (r->y + 1)) ||
            (x == (r->x + 2) &&  y == (r->y + 1)) ||
            (x == (r->x - 1) &&  y == (r->y + 2)) ||
            (x == (r->x + 1) &&  y == (r->y + 2))
        )
        {
            v ++;
            r = route_next(r, x, y, SMALL_L);
            board->grids[i] = r;

            used = 0;

            for (j = 0; j < length; j++)
            {
                if ( board->grids[j] )
                {
                    used ++;
                }

            }

            if ( r->stepNo > maxLength )
            {
                maxRoute = route_copy(board->route);
                maxLength = r->stepNo;
            }

            if (0 && used == length )
            {
                board_print(board);
                printf("\n");
                break;
            }

            //SMALL_L
            for (j = 0; j < length; j++)
            {
                if( board->grids[j] )
                {
                    continue;
                }
                x = j % board->sizeN;
                y = j / board->sizeN;
                if(
                    (x == (r->x - 1) &&  y == (r->y - 1)) ||
                    (x == (r->x + 1) &&  y == (r->y - 1)) ||
                    (x == (r->x - 1) &&  y == (r->y + 1)) ||
                    (x == (r->x + 1) &&  y == (r->y + 1))
                )
                {
                    r2 = route_next(r, x, y, BIG_L);
                    board->grids[j] = r2;

                    if ( r2->stepNo > maxLength )
                    {
                        maxRoute = route_copy(board->route);
                        maxLength = r2->stepNo;
                    }

                    last = r2;
                    adam_dfs2(board);
                    board->grids[j] = NULL;
                    route_destory(r2);
                }
            }

            board->grids[i] = NULL;
            last = r->prev;
            route_destory(r);
        }
    }

    //route_destory(b->route);
    //board_destory(b);

    // no next move;
    //if(length == used)
    //{
    //    board_print(board);
    //}

    return board;
}

BOARD *
adam_dfs3(BOARD *board)
{
    unsigned length, i, j, ii, jj;
    int x, y;
    ROUTE *r, *r2, *r3, *r4;

    if(!board->route)
    {
        return board;
    }

    length = board_length(board);

    if (!last)
    {
        last = route_last(board->route);
    }

    for(i = 0; i < length; i++)
    {
        r = last;

        if( board->grids[i] )
        {
            continue;
        }

        x = i % board->sizeN;
        y = i / board->sizeN;

        // BIG_L
        if (
            (x == (r->x - 1) &&  y == (r->y - 2)) ||
            (x == (r->x + 1) &&  y == (r->y - 2)) ||
            (x == (r->x - 2) &&  y == (r->y - 1)) ||
            (x == (r->x + 2) &&  y == (r->y - 1)) ||
            (x == (r->x - 2) &&  y == (r->y + 1)) ||
            (x == (r->x + 2) &&  y == (r->y + 1)) ||
            (x == (r->x - 1) &&  y == (r->y + 2)) ||
            (x == (r->x + 1) &&  y == (r->y + 2))
        )
        {
            r = route_next(r, x, y, SMALL_L);
            board->grids[i] = r;

            if ( r->stepNo > maxLength )
            {
                maxRoute = route_copy(board->route);
                maxLength = r->stepNo;
            }

            //SMALL_L
            for (j = 0; j < length; j++)
            {
                if( board->grids[j] )
                {
                    continue;
                }

                x = j % board->sizeN;
                y = j / board->sizeN;

                if(
                    (x == (r->x - 1) &&  y == (r->y - 1)) ||
                    (x == (r->x + 1) &&  y == (r->y - 1)) ||
                    (x == (r->x - 1) &&  y == (r->y + 1)) ||
                    (x == (r->x + 1) &&  y == (r->y + 1))
                )
                {
                    r2 = route_next(r, x, y, BIG_L);
                    board->grids[j] = r2;

                    if ( r2->stepNo > maxLength )
                    {
                        maxRoute = route_copy(board->route);
                        maxLength = r2->stepNo;
                    }

                    for (ii = 0; ii < length; ii++)
                    {
                        if( board->grids[ii] )
                        {
                            continue;
                        }

                        x = ii % board->sizeN;
                        y = ii / board->sizeN;

                        // BIG_L
                        if (
                            (x == (r2->x - 1) &&  y == (r2->y - 2)) ||
                            (x == (r2->x + 1) &&  y == (r2->y - 2)) ||
                            (x == (r2->x - 2) &&  y == (r2->y - 1)) ||
                            (x == (r2->x + 2) &&  y == (r2->y - 1)) ||
                            (x == (r2->x - 2) &&  y == (r2->y + 1)) ||
                            (x == (r2->x + 2) &&  y == (r2->y + 1)) ||
                            (x == (r2->x - 1) &&  y == (r2->y + 2)) ||
                            (x == (r2->x + 1) &&  y == (r2->y + 2))
                        )
                        {
                            r3 = route_next(r2, x, y, SMALL_L);
                            board->grids[ii] = r3;

                            if ( r3->stepNo > maxLength )
                            {
                                maxRoute = route_copy(board->route);
                                maxLength = r3->stepNo;
                            }

                            //SMALL_L
                            for (jj = 0; jj < length; jj++)
                            {
                                if( board->grids[jj] )
                                {
                                    continue;
                                }
                                x = jj % board->sizeN;
                                y = jj / board->sizeN;
                                if(
                                    (x == (r3->x - 1) &&  y == (r3->y - 1)) ||
                                    (x == (r3->x + 1) &&  y == (r3->y - 1)) ||
                                    (x == (r3->x - 1) &&  y == (r3->y + 1)) ||
                                    (x == (r3->x + 1) &&  y == (r3->y + 1))
                                )
                                {
                                    r4 = route_next(r3, x, y, BIG_L);
                                    board->grids[jj] = r2;

                                    if ( r4->stepNo > maxLength )
                                    {
                                        maxRoute = route_copy(board->route);
                                        maxLength = r4->stepNo;
                                    }

                                    last = r4;
                                    adam_dfs3(board);
                                    board->grids[jj] = NULL;
                                    route_destory(r4);
                                }
                            }

                            board->grids[ii] = NULL;
                            route_destory(r3);
                        }

                    }

                    board->grids[j] = NULL;
                    route_destory(r2);
                }
            }

            board->grids[i] = NULL;
            last = r->prev;
            route_destory(r);
        }
    }

    //route_destory(b->route);
    //board_destory(b);

    // no next move;
    //if(length == used)
    //{
    //    board_print(board);
    //}

    return board;
}


/*BOARD *
adam_dfs_SS(BOARD *board)
{

    unsigned length, i, used = 0;
    int x, y;
    BOARD *b;
    ROUTE *r, *rLast;

    if(!board->route)
    {
        return board;
    }

    length = board_length(board);

    b = board_copy(board);

    rLast = route_last(b->route);
    for(i = 0; i < length; i++)
    {
        r = rLast;

        if( b->grids[i] )
        {
            used ++;
            continue;
        }

        x = i % board->sizeN;
        y = i / board->sizeN;

        if (
            (x == (r->x - 1) &&  y == (r->y - 1)) ||
            (x == (r->x + 1) &&  y == (r->y - 1)) ||
            (x == (r->x - 1) &&  y == (r->y + 1)) ||
            (x == (r->x + 1) &&  y == (r->y + 1))
        )
        {
            r = route_next(r, x, y, SMALL_L);
            b->grids[i] = r;
            adam_dfs_SS(b);
            b->grids[i] = NULL;
            route_destory(r);
        }
    }

    // no next move;
    if ( rLast->stepNo > maxLength )
    {
        if( (maxRoute))
        {
            route_destory(maxRoute);
        }
        maxRoute = route_copy(b->route);
        maxLength = rLast->stepNo;
    }

    route_destory(b->route);
    board_destory(b);

    return board;
}*/
