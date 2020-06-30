#ifndef QHELPER_H
#define QHELPER_H

#include "head.h"

class QHelper
{
public:
    //关闭其他相同进程，避免多开
    static void Close_other(const QString);

    //判断IP地址及端口是否在线
    static bool ipLive(const QString &ip, int port, int out = 1000);

    //设置开机自启动
    static void runWithSystem(const QString &strName, const QString &strPath, bool autoRun = true);

    //程序本身文件名称
    static QString appName();

    //程序当前所在路径
    static QString appPath();

    //初始化随机数种子
    static void initRand();

    //日志模块
    static void writ_log(QString str_log ,int line ,QString file);

    //关闭软件
    static void closeAll();

    //对文件某行进行删除操作
    static int delete_line(QFile* file,int delete_num);

    //延时操作
    static void Delay_MSec(unsigned int msec);

};

#endif // QHELPER_H
