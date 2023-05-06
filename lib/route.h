#ifndef __ROUTE_H__
#define __ROUTE_H__

#define BIG_L 'L'
#define SMALL_L 'l'

// ROUTE
typedef struct ROUTE ROUTE;

struct ROUTE
{
    // pointer to next ROUTE
    ROUTE *next;
    // pointer to previous ROUTE
    ROUTE *prev;

    // (x, y)
    int x;
    int y;
    unsigned nextMove;

    // No. of this step
    unsigned stepNo;
};
// copy the route
ROUTE *route_copy(ROUTE *oldRoute);

// destroy the route
void route_destory(ROUTE *route);

// create route start with (x, y) and a stepNo
ROUTE *route_create(unsigned x, unsigned y, unsigned stepNo, unsigned nextMove);

// print the route
void route_print(ROUTE *route);

// add next one to the route
ROUTE *route_next(ROUTE *route, unsigned x, unsigned y, unsigned nextMove);

// get route length
unsigned route_length(ROUTE *route);

// get last one of the route
ROUTE *route_last(ROUTE *route);

#endif
