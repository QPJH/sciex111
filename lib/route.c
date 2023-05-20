#include "route.h"
#include <stdlib.h>
#include <stdio.h>

// copy the route
ROUTE *
route_copy(ROUTE *oldRoute)
{
    ROUTE *newRoute, *next;

    // create new route like oldRoute
    newRoute = route_create(oldRoute->x, oldRoute->y, oldRoute->stepNo, oldRoute->nextMove);

    if(oldRoute->next)
    {
        // copy route->next
        next = route_copy(oldRoute->next);
        newRoute->next = next;
        newRoute->next->prev = newRoute;
    }

    return newRoute;
}

// destroy the route
void route_destory(ROUTE *route)
{
    if(route->prev)
    {
        route->prev->next = NULL;
    }

    if (route->next)
    {
        route_destory(route->next);
        free(route->next);
        route->next = NULL;
    }

    free(route);
    route = NULL;
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
    if(route->next)
    {
        return route_last(route->next);
    }

    return route;
}
