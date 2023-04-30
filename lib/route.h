#ifndef __ROUTE_H__
#define __ROUTE_H__

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

    // No. of this step
    unsigned stepNo;
};

// destroy the route
void route_destory(ROUTE *route);

// create route start with (x, y) and a stepNo
ROUTE *route_create(unsigned x, unsigned y, unsigned stepNo);

// print the route
void route_print(ROUTE *route);

// add next one to the route
ROUTE *route_next(ROUTE *route, unsigned x, unsigned y);

#endif
