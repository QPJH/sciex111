#include <stdlib.h>
#include <stdio.h>
#include "board.h"
#include "route.h"

// destory the board
void board_destory(BOARD *board)
{
    unsigned i;

    if (board->route)
    {
        // don't clean if board has a running route
        return;
    }

    for (i = 0; i < board_length(board); i++)
    {
        // board->grids[i] is a (ROUTE *)
        if(!board->grids[i]) {
            continue;
        }
        free(board->grids[i]);
        board->grids[i] = NULL;
    }

    free(board);
    board = NULL;
}

// create a board with size (N, M)
BOARD *
board_create(unsigned sizeN, unsigned sizeM)
{
    BOARD *board;

    board = malloc(sizeof(BOARD));
    board->sizeN = sizeN;
    board->sizeM = sizeM;
    board->grids = malloc(sizeN * sizeM * sizeof(ROUTE*));

    return board;
}

// get board length
unsigned
board_length(BOARD *board)
{
    return board->sizeN * board->sizeM;
}
