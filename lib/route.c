#include "route.h"
#include <stdlib.h>
#include <stdio.h>

// copy the route
ROUTE *
route_copy(ROUTE *oldRoute)
{
    ROUTE *newRoute, *n,*r;

    // create new route like oldRoute
    newRoute = route_create(oldRoute->x, oldRoute->y, oldRoute->stepNo, oldRoute->nextMove);
    n=newRoute;
    for(r=oldRoute->next; r; r=r->next)
    {
        n = route_next(n,r->x,r->y,r->nextMove);
    }
    return newRoute;
}

// destroy the route
void route_destory(ROUTE *route)
{
    ROUTE *r;

    if (route->prev)
    {
        route->prev->next = NULL;
    }

    route->prev = NULL;

    r = route_last(route);

    for(r = route_last(route); r;)
    {
        if (r->prev)
        {
            r = r->prev;
            free(r->next);
        }
        else
        {
            // r has no previous, so break;
            break;
        }
    }
}

// create route start with (x, y) and a stepNo, nextMove
ROUTE *route_create(unsigned x, unsigned y, unsigned stepNo, unsigned nextMove)
{
    ROUTE *route;

    route = malloc(sizeof(ROUTE));
    route->stepNo = stepNo;
    route->nextMove = nextMove;
    route->x = x;
    route->y = y;
    route->prev = NULL;
    route->next = NULL;

    return route;
}

// print the route
void route_print(ROUTE *route)
{
    ROUTE *r;

    for(r = route; r; r = r->next)
    {
        printf("#%d (%d, %d)\n", r->stepNo, r->x, r->y);
    }
}

// add next one to the route
ROUTE *
route_next(ROUTE *route, unsigned x, unsigned y, unsigned nextMove)
{
    ROUTE *next = route_create(x, y, route->stepNo + 1, nextMove);
    next->prev = route;
    route->next = next;

    return next;
}

// get route length
unsigned
route_length(ROUTE *route)
{
    ROUTE *r;
    int length=0;
    for(r=route; r; r = r->next)
    {
        length=length + 1;
    }

    return length;
}

// get last one of the route
ROUTE *
route_last(ROUTE *route)
{
    ROUTE *r;

    for (r = route; r; r = r->next)
    {
        if(!r->next)
        {
            return r;
        }
    }

    return route;
}
