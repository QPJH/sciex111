#include <stdio.h>
#include "route.h"
#include "board.h"
#include "adam.h"

int completedCount = 0;
int completed[1000000][128];

int *board_getCompleted(BOARD *board)
{
    int i, j, length, used;
    ROUTE *r;

    length = board_length(board);
    r = route_last(board->route);

    if (r->stepNo < 16)
    {
        return NULL;
    }

    for (i = 0; i < completedCount; i++)
    {
        if (r->stepNo == completed[i][0])
        {
            used = 0;
            for (j = 0; j < length; j++)
            {
                if (board->grids[j])
                {
                    if (completed[i][used + 1] != j)
                    {
                        break;
                    }
                    used ++;
                }
            }

            if (j == length)
            {
                // every grids all are same
                return completed[i];
            }
        }
    }

    return NULL;
}

void board_markCompeleted(BOARD *board)
{
    ROUTE *r;
    int i, used, length;

    length = board_length(board);
    r = route_last(board->route);

    if( r->stepNo < 16)
    {
        return;
    }
    completed[completedCount][0] = r->stepNo;

    used = 0;
    for (i = 0; i < length; i++)
    {
        if (board->grids[i])
        {
            completed[completedCount][used + 1] = i;
            used ++;
        }
    }
    completedCount++;
}

int maxLength = 0;
ROUTE *maxRoute = NULL;
ROUTE *last = NULL;

ROUTE *
adam_dfsRoute(BOARD *board)
{
    adam_dfs2(board);

    return maxRoute;
}

BOARD *
adam_dfs(BOARD *board)
{
    unsigned length, i, used = 0;
    int x, y;
    BOARD *b;
    ROUTE *r;

    if(!board->route)
    {
        return board;
    }

    length = board_length(board);

    b = board_copy(board);

    for(i = 0; i < length; i++)
    {
        r = route_last(b->route);

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
    route_destory(b->route);
    board_destory(b);

    // no next move;
    if(length == used)
    {
        board_print(board);
    }

    return board;
}

BOARD *
adam_dfs2(BOARD *board)
{
    unsigned length, i, j, used = 0;
    int x, y;
    BOARD *b;
    ROUTE *r, *r2;

    if(!board->route)
    {
        return board;
    }

    length = board_length(board);

    if (!last) {
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

            used = 0;

            for (j = 0; j < length; j++)
            {
                if ( board->grids[j] )
                {
                    used ++;
                }

            }

            if ( r->stepNo > maxLength)
            {
                maxRoute = route_copy(board->route);
                maxLength = r->stepNo;
            }

            if ( used == length )
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
    unsigned length, i, j, used = 0;
    int x, y;
    BOARD *b;
    ROUTE *r, *r2;


    if (board_getCompleted(board))
    {
        return board;
    }

    board_markCompeleted(board);

    if(!board->route)
    {
        return board;
    }

    length = board_length(board);

    for(i = 0; i < length; i++)
    {
        r = route_last(board->route);

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

            used = 0;

            for (j = 0; j < length; j++)
            {
                if ( board->grids[j] )
                {
                    used ++;
                }

            }


            if ( used == length )
            {
                board_print(board);
                printf("\n");

                board->grids[i] = NULL;
                route_destory(r);

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
                    adam_dfs3(board);
                    board->grids[j] = NULL;
                    route_destory(r2);
                }
            }

            board->grids[i] = NULL;
            route_destory(r);
        }
    }

    // route_destory(b->route);
    // board_destory(b);

    // no next move;
    //if(length == used)
    //{
    //    board_print(board);
    //}

    return board;
}
