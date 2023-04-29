#ifndef __BOARD_H__
#define __BOARD_H__

#include "route.h"

// 一個棋盤結構
typedef struct BOARD BOARD;

struct BOARD
{
    // 總共有 sizeX * sizeY 個格子
    int sizeX;
    int sizeY;
    // for cord(x, y), n for index of grid[n], n = x + y*(sizeX)

    ROUTE *route;   // 指標: 指向正在進行中路線
    ROUTE **grids;  // 指標陣列: 每個陣列中的指標指向棋盤的一維地址
                    // **grids[n] 可以用來檢查某一個格子是不是已被走過, 已被走過會指向一個路線
};

// 清除棋盤和路線
void board_destory(BOARD *board);

// 建立一個 sizeX * sizeY 的棋盤
BOARD * board_create(unsigned sizeX, unsigned sizeY);

// 取得棋盤的一維長度, 對於座標(x, y)的格子, 他的一維地址 = x + y*sizeX
unsigned board_length(BOARD *board);
#endif
