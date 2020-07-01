#ifndef CHESS_H
#define CHESS_H

#include <QObject>
#include "help/head.h"

class Chess : public QObject
{
    Q_OBJECT
public:
    static Chess *Instance();
    explicit Chess(QObject *parent = 0);

private:
    static QScopedPointer<Chess> self;

    vChess* LcoalvChess;

private slots:
    //AI下棋
    void ChessAI();

signals:
    //棋盘显示更新
    void UpdateShow();
    //游戏结束,1-白胜 -1-黑胜
    void GameOver(int);
    //添加棋子结束信号
    void addOver(int next);

public slots:
    void start();
    void setConnInfo(vChess* inchess);
    void actionAddPiece(int row ,int col);      //棋子增加函数
};

#endif // CHESS_H
