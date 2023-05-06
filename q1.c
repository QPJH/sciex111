#include <stdio.h>
#include "lib/route.h"
#include "lib/board.h"
#include "lib/L_4x4_half_1.h"
#include "lib/LL_4x4_half_1.h"

int main()
{
    BOARD *board1, *board2, *board3, *board;
    ROUTE *route, *last;

    // 半成品1
    // board_destory(board);

    //4x4_L_half_1
    printf("大馬開始的4x4半成品1\n");
    board1 = L_4x4_half_1();
    board_svg(board1);
    board_print(board1);


    printf("小馬開始的4x4半成品2\n");
    board2 = LL_4x4_half_1();
    board_print(board2);

    printf("小馬開始的4x4完成品\n");
    board3 = board_create(4, 4);
    route = route_create(2, 0, 1, SMALL_L);
    last = route_next(route, 3, 1, BIG_L);  // last is (3, 1)
    last = route_next(last, 2, 3, SMALL_L); // last is (2, 3)
    last = route_next(last, 3, 2, BIG_L);
    last = route_next(last, 1, 3, SMALL_L);
    last = route_next(last, 0, 2, BIG_L);
    last = route_next(last, 1, 0, SMALL_L);
    last = route_next(last, 0, 1, BIG_L);
    last = route_next(last, 2, 2, SMALL_L);
    last = route_next(last, 3, 3, BIG_L);
    last = route_next(last, 1, 2, SMALL_L);
    last = route_next(last, 0, 3, BIG_L);
    last = route_next(last, 1, 1, SMALL_L);
    last = route_next(last, 0, 0, BIG_L);
    last = route_next(last, 2, 1, SMALL_L);
    last = route_next(last, 3, 0, BIG_L);
    board_addRoute(board3, route);  // 把路線放到 board3
    board_print(board3);

    // 把 3 個 board 拼起來
    route = board_mergeRoute(board1, board2, 0, board1->sizeM);
    board = board_create(4, 4*2);
    board_addRoute(board, route);   // 把路線放到 board

    route = board_mergeRoute(board, board3, 0, board->sizeM);
    // 重複使用 board 指標前先 destory board 釋放記憶體
    board_destory(board);

    board = board_create(4*10, 4*3*10);   // 重複使用 board
    board_addRoute(board, route);   // 把路線放到 board

    printf("合併3個board\n");
    board_svg(board);

    // 用過的指標都要 destory
    route_destory(board->route);
    board_destory(board);
    board_destory(board1);
    board_destory(board2);
    board_destory(board3);

    return 0;
}
