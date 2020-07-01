#ifndef APPINIT_H
#define APPINIT_H

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
    //界面初始化
    void initShow();

    //Chess模块初始化
    void initChess();

    //判断初始化
    void initJudge();

    //AI初始化
    void initAIdo();

public slots:
    //程序启动函数
    void start();
};

#endif // APPINIT_H
