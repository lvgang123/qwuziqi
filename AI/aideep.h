#ifndef AIDEEP_H
#define AIDEEP_H

/**
 * 深度计算推演 整理:lvgang 2020-7-3
 */

#include "aicore.h"

class AIdeep
{
public:
    static AIdeep *Instance();
    explicit AIdeep();
    ~AIdeep();

private:
    static unique_ptr<AIdeep> self;
    int LocalLength;
    vChess scoreMapVec;
    vChess LocalvChess;

private:
    void initScoreVec();
    vector<CPoint> Select_max(vChess calchess,vChess nowchess);                                //挑选出最大分数的几个点
    CPoint Select_Point(vector<CPoint> vPoints);        //从容器中筛选出最大值并随机抽取
    int empty_cout(vChess calchess);                    //获取空位置
    void debuge_vchess(vChess outMapVec);               //Vchess数据打印函数
    vChess copyvChess(vChess invchess);

public:
    void start();                                       //模块启动函数
    void setConnInfo(int length);                       //模块设定
    CPoint Get_deepRsult(vChess calchess,int deep
                         ,int calColor);                       //深度计算
};

#endif // AIDEEP_H
