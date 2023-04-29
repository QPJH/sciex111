#ifndef __ROUTE_H__
#define __ROUTE_H__

// 一個路線結構
typedef struct ROUTE ROUTE;

struct ROUTE
{
    // 此路線的 next 指向下一步的路線, 簡單說就是個 LinkedList 資料結構
    ROUTE *next;
    // 此路線的 prev 指向前一步的路線, 用於無路可走的時候往前搜尋
    ROUTE *prev;

    // x, y 代表目前路線使用到的座標, 要與棋盤座標系配合才能得知他再棋盤上的一維地址
    int x;
    int y;

    // 第幾步
    unsigned stepNo;
};

// 清除路線
void route_destory(ROUTE *route);

// 建立新的路線於 (x, y)
ROUTE *route_create(unsigned x, unsigned y, unsigned stepNo);

// 印出路線的座標
void route_print(ROUTE *route);

// 路線加入下一步
ROUTE *route_next(ROUTE *route, unsigned x, unsigned y);

#endif
