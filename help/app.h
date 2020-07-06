#ifndef APP_H
#define APP_H

/**
 * 全局变量及配置文件 整理:lvgang 2020-6-30
 */
#include "head.h"

class APP
{
public:
    //软件模式变量
    static int WorkModle;               //下棋模式，0-人机  1-人人
    static int AIColor;                 //AI持棋子颜色,白子1，黑子-1

    //棋盘数组
    static vChess gameMapVec;           //当前游戏棋盘和棋子的情况,空白为0，

    //棋盘布局
    static int kBoardSizeNum;           // 棋盘尺寸
    static int kBoardMargin;            // 棋盘边缘空隙
    static int kRadius;                 // 棋子半径
    static int kMarkSize;               // 落子标记边长
    static int kBlockSize;              // 格子的大小
    static int kPosDelta;               // 鼠标点击的模糊距离上限
    static int kAIDelay;                // AI下棋的思考时间

    //全局变量
    static bool Show_waite;             //绘制等待位
    static int deepA;                   //黑子计算深度
    static int deepB;                   //白字计算深度
    static LChess scoreA;               //黑子分值数据
    static LChess scoreB;               //白子分值数据

    //初始化棋盘函数
    static void initchess();
    static void initScore();

};

#endif // APP_H
