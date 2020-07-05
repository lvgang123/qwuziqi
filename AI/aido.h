#ifndef AIDO_H
#define AIDO_H

/**
 * AI下棋Demo 整理:lvgang 2020-7-2
 * 1.该模块接口函数为（actionByAI），调用函数即可获得计算出的行和列
 * 2.模块设定函数：传入棋盘，将AI的棋子颜色传入
 * 该模块目前主要思路：
 * 对棋盘中的空位置的八个方向取出9个棋子放入容器中（GetTran函数）
 * 将得到的容器每个方向视为一行，对每一行进行筛选（比如0，-1，-1,2，0,1,1，10,10）筛选为杀:（0，-1，-1,2，-1） 成:（2,0,1,1）
 * 将筛选出的进行判断，具体判断间linejudge
 */

#include "aideep.h"

class AIDO
{
public:
    static AIDO *Instance(const int num);
    explicit AIDO();
    ~AIDO();

private:
    static unique_ptr<AIDO> self[2];

    vChess* LocalvChess;
    int LocalAICorlor;
    int Localdeep;

private:


public:
    void start();                                       //模块启动函数
    void setConnInfo(vChess* inchess,int deep,
                     const int AIcolor);                //模块设定
    void actionByAI(int &row,int &col);                 //AI模块调用函数，用于获取AI下一步
};

#endif // AIDO_H
