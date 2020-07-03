#ifndef CHESSER_H
#define CHESSER_H

/**
 * 棋手模块 整理:lvgang 2020-6-30
 * 1.计算棋子，并在棋盘下下棋
 */

#include <QObject>
#include "help/head.h"

class Chesser : public QObject
{
    Q_OBJECT
public:
    static Chesser *Instance();
    explicit Chesser(QObject *parent = 0);

private:
    static QScopedPointer<Chesser> self;
    QTimer *timer_AI;                       //机器定时检查是否该自己下棋

private slots:


signals:
    void actionByAI(int row ,int col);

public slots:
    void start();                           //模块启动函数
    void setConnInfo();                     //模块设定函数
    void stop();                           //模块停止函数
    void AIplayA();                         //A电脑增加
    void AIplayB();                         //B电脑增加
};

#endif // CHESSER_H
