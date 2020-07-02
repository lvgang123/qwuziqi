#ifndef APPINIT_H
#define APPINIT_H

/**
 * 程序初始化模块 整理:lvgang 2020-6-30
 * 1.start()在main函数中被调用，用于启动整个应用程序
 * 2.同时对各个模块进行初始化，初始化包含模块的设定和信号槽的连接
 */

#include <QObject>
#include "help/head.h"

class AppInit : public QObject
{
    Q_OBJECT
public:
    static AppInit *Instance();
    explicit AppInit(QObject *parent = 0);

private:
    static QScopedPointer<AppInit> self;

private slots:
    void initShow();        //界面初始化
    void initChess();       //Chess模块初始化
    void initJudge();       //判断初始化
    void initAIdo();        //AI初始化

public slots:
    void start();           //程序启动函数
};

#endif // APPINIT_H
