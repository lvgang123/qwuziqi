#ifndef JUDGEMODEL_H
#define JUDGEMODEL_H

/**
 * 判断模块模块 整理:lvgang 2020-6-30
 * 1.判断对局是否结束，是否和局
 * 2.判断下一步是黑棋走还是白棋
 */

#include <QObject>
#include "help/head.h"

class JudgeModel : public QObject
{
    Q_OBJECT
public:
    static JudgeModel *Instance();
    explicit JudgeModel(QObject *parent = 0);

private:
    static QScopedPointer<JudgeModel> self;

    vChess* LocalvChess;

private slots:


public slots:
    void start();                           //模块启动函数
    void setConnInfo(vChess* inchess);      //模块设定函数
    bool isWin(int row ,int col);           //判断对局是否结束
    bool isDeadGame();                      //判断是否和棋
    int NextColour();                       //判断下一步是黑棋还是白起

};

#endif // JUDGEMODEL_H
