#include <stdio.h>
#include "route.h"
#include "board.h"
#include "allen.h"
#include "adam.h"

int allen_maxLength = 0;
ROUTE *allen_maxRoute = NULL;
ROUTE *allen_last = NULL;


ROUTE *
allen_dfsRoute(BOARD *board)
{
    adam_dfs_SS(board);

    return allen_maxRoute;
}

BOARD *
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
    if ( rLast->stepNo > allen_maxLength )
    {
        if( (allen_maxRoute))
        {
            route_destory(allen_maxRoute);
        }
        allen_maxRoute = route_copy(b->route);
        allen_maxLength = rLast->stepNo;
    }

    route_destory(b->route);
    board_destory(b);

    return board;
}
