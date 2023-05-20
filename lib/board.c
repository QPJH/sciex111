#include <stdlib.h>
#include <stdio.h>
#include "board.h"
#include "route.h"

// copy the board
BOARD *
board_copy(BOARD *oldBoard)
{
    BOARD *newBoard;
    ROUTE *newRoute;

    newBoard = board_create(oldBoard->sizeN, oldBoard->sizeM);
    newRoute = route_copy(oldBoard->route);

    board_addRoute(newBoard, newRoute);

    return newBoard;
}

// destory the board
void board_destory(BOARD *board)
{
    free(board->grids);
    free(board);
    board = NULL;
}

// create a board with size (N, M)
BOARD *
board_create(unsigned sizeN, unsigned sizeM)
{
    BOARD *board;
    unsigned i;

    board = malloc(sizeof(BOARD));
    board->sizeN = sizeN;
    board->sizeM = sizeM;
    board->grids = malloc(sizeN * sizeM * sizeof(ROUTE*));
    board->route = NULL;

    for (i = 0; i < sizeN*sizeM; i++)
    {
        board->grids[i] = NULL;
    }

    return board;
}

// get board length
unsigned
board_length(BOARD *board)
{
    return board->sizeN * board->sizeM;
}

// print the board
void
board_print(BOARD *board)
{
    unsigned i, length;
    ROUTE *r;

    length = board_length(board);
    if(length == 0)
    {
        // no size
        printf("Not a board");
        return;
    }

    for(i = 0; i < length; i++)
    {
        r = board->grids[i];
        if(r)
        {
            printf(" %3d", r->stepNo);
        }
        else
        {
            printf("    ");
        }

        if((i+1) % board->sizeN == 0)
        {
            printf("\n");
        }
    }
}

// svg board image
void
board_svg(BOARD *board)
{
    ROUTE *r;
    FILE *fp;
    unsigned length, sizeN, sizeM, i;
    char buf[128];

    length = board_length(board);
    if(length == 0)
    {
        // no size
        printf("Not a board");
        return;
    }

    sprintf(buf, "%dx%d.svg", board->sizeN, board->sizeM);
    fp = fopen(buf, "w+");

    sizeN = board->sizeN * BOARD_SVG_SCALE;
    sizeM = board->sizeM * BOARD_SVG_SCALE;

    fprintf(fp, "<svg width=\"%d\" height=\"%d\" version=\"1.1\" viewBox=\"0 0 %d %d\" xmlns=\"http://www.w3.org/2000/svg\">\n", sizeN, sizeM, sizeN, sizeM);
    fprintf(fp, "<g transform=\"translate(0,0) scale(%d)\">\n", BOARD_SVG_SCALE);

    // grids
    fprintf(fp, "<g fill=\"white\" stroke=\"gray\" stroke-width=\"0.025\">\n");
    fprintf(fp, "<rect x=\"0\" y=\"0\" width=\"%d\" height=\"%d\" />\n", board->sizeN, board->sizeM);

    for (i = 1; i < board->sizeN; i++)
    {
        fprintf(fp, "<line x1=\"%d\" y1=\"0\" x2=\"%d\" y2=\"%d\" />\n", i, i, board->sizeM);
    }

    for (i = 1; i < board->sizeM; i++)
    {
        fprintf(fp, "<line x1=\"0\" y1=\"%d\" x2=\"%d\" y2=\"%d\" />\n", i, board->sizeN, i);
    }
    fprintf(fp, "</g>\n");

    // polyline
    fprintf(fp, "<g transform=\"translate(0.5,0.5)\">");
    for (r = board->route; r ; r = r->next)
    {
        if (r->next)
        {
            fprintf(fp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"%s\" stroke-width=\"0.05\"/>", r->x, r->y, r->next->x, r->next->y, r->nextMove == BIG_L ? "green" : "yellow");
        }
    }
    for (r = board->route; r ; r = r->next)
    {
        if (r->stepNo < 1000)
        {
            fprintf(fp, "<text dominant-baseline=\"middle\" text-anchor=\"middle\" x=\"%d\" y=\"%d\" dx=\"-0.1\" dy=\"0.1\" font-size=\"0.5\">%d</text>\n", r->x, r->y, r->stepNo);
        }
    }
    fprintf(fp, "</g>\n");

    fprintf(fp, "</g>\n");
    fprintf(fp, "</svg>\n");
    fflush(fp);
    // if(fp) {
    //     fclose(fp);
    //     fp = NULL;
    // }
}

// add a route to the board
void
board_addRoute(BOARD *board, ROUTE *route)
{
    unsigned index;
    ROUTE *r;

    if(board_length(board) == 0)
    {
        // no size
        return;
    }

    if(board->route)
    {
        // already has a route
        return;
    }

    // assign the route
    board->route = route;

    if(route)
    {
        // refresh the grids
        for(r = route; r; r = r->next)
        {
            index = board_XY2Index(board, r->x, r->y);
            board->grids[index] = r;
        }
    }
}

// get (x, y) grids index of the board
int
board_XY2Index(BOARD *board, unsigned x, unsigned y)
{
    if(board_length(board) == 0)
    {
        return -1;
    }

    return x + board->sizeN * y;
}

// merge board and return route
ROUTE *
board_mergeRoute(BOARD *bFrom, BOARD *bTo, unsigned x, unsigned y)
{
    ROUTE *route, *r;

    route = route_last(bFrom->route);
    route->next = bTo->route;
    route->next->prev = route;

    for(r = route->next; r; r = r->next)
    {
        r->stepNo = r->stepNo + route->stepNo;
        r->x = r->x + x;
        r->y = r->y + y;
    }

    return bFrom->route;
}
