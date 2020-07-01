#ifndef JUDGEMODEL_H
#define JUDGEMODEL_H

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

    vChess* LcoalvChess;

private slots:


public slots:
    void start();
    void setConnInfo(vChess* inchess);

    //判断对局是否结束
    bool isWin(int row ,int col);
    //判断是否和棋
    bool isDeadGame();
    //判断下一步是黑棋还是白起
    int NextColour();

};

#endif // JUDGEMODEL_H
