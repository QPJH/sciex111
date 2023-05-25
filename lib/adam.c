#include <stdio.h>
#include "route.h"
#include "board.h"

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
        fflush(stdout);
        printf("\n");
    }
    return board;
}
