#include "route.h"
#include <stdlib.h>
#include <stdio.h>

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

// create route start with (x, y) and a stepNo
ROUTE *route_create(unsigned x, unsigned y, unsigned stepNo)
{
    ROUTE *route;

    route = malloc(sizeof(ROUTE));
    route->stepNo = stepNo;
    route->x = x;
    route->y = y;
    route->next = NULL;    

    return route;
}

// print the route
void route_print(ROUTE *route)
{
    printf("#%d (%d, %d)\n", route->stepNo, route->x, route->y);
    if(route->next)
    {
        route_print(route->next);
    }
}

// add next one to the route
ROUTE *route_next(ROUTE *route, unsigned x, unsigned y)
{
    ROUTE *next = route_create(x, y, route->stepNo + 1);
    next->prev = route;
    route->next = next;

    return next;
}
