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

public:
    void start();                                       //模块启动函数
    void setConnInfo();                                 //模块设定
};

#endif // AICORE_H
