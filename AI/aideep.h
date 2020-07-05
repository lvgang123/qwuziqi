#ifndef AIDEEP_H
#define AIDEEP_H

/**
 * 深度计算推演 整理:lvgang 2020-7-3
 */

#include "chead.h"

class AIdeep
{
public:
    static AIdeep *Instance();
    explicit AIdeep();
    ~AIdeep();

private:
    static unique_ptr<AIdeep> self;

public:
    void start();                                       //模块启动函数
    void setConnInfo();                                 //模块设定
};

#endif // AIDEEP_H
