#ifndef AICORE_H
#define AICORE_H

/**
 * 分数计算核心 整理:lvgang 2020-7-3
 */
#include "chead.h"

class AICore
{
public:
    static AICore *Instance();
    explicit AICore();
    ~AICore();

private:
    static unique_ptr<AICore> self;

    vChess scoreMapVec;
    int LocalLength;
    int LocalAICorlor;
    LChess Localscore;                                  //

private:
    void debuge_vchess(vChess outMapVec);               //Vchess数据打印函数
    void initScoreVec();                                //初始化评分数组
    void GetTran(int row,int col,vChess &tranMapVec
                 ,vChess calchess);                     //得到中间数组
    void DealTran(vChess tranMapVec
                  ,vChess &killMapVec
                  ,vChess &makeMapVec);                 //整合中间数组
    int CalculateTran(vChess killMapVec
                       ,vChess makeMapVec,int index);             //计算中间数组
    int linejudge(LChess onekill,int level
                  ,bool active,int judge_it);           //判定是否为2-5杀,并判定两边活点

public:
    void start();                                       //模块启动函数
    void setConnInfo(int length);                                 //模块设定
    vChess calculateScore(vChess calchess,int calCorlor
                          ,int index=0);                              //计算评分数组,index:0-杀和成都计算 -1-杀 1-成
    void setScore(LChess scores);                           //设置分数
};

#endif // AICORE_H
