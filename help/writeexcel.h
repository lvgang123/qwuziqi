#ifndef WRITEEXCEL_H
#define WRITEEXCEL_H

#include "head.h"
#include <QtXlsx/QtXlsx>

//分值修正存储结构
struct Excel_Score
{
    QDateTime addtime;      //添加时间
    int type;               //棋子类型
    int def_count=0;
    int boot_min=0;
};

class WriteExcel
{
public:
    WriteExcel();
};

#endif // WRITEEXCEL_H
