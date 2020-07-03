#ifndef CHESS_H
#define CHESS_H

/**
 * 棋盘模块 整理:lvgang 2020-6-30
 * 1.为整个棋盘的添加棋子（actionAddPiece）
 * 2.当发现棋盘添加时发送信号进行界更新（UpdateShow）
 * 3.调用AI模块完成AI下棋（ChessAI）
 */

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
    int count_record = 0;
    int time_record = 0;

private slots:

signals:
    void UpdateShow();                  //棋盘显示更新
    void GameOver(int);                 //游戏结束,1-白胜 -1-黑胜
    void addOver(int next);             //添加棋子结束信号

public slots:
    void start();                       //模块启动函数
    void setConnInfo(vChess* inchess);  //模块设定函数
    void actionAddPiece(int row ,
                        int col);       //棋子增加函数
};

#endif // CHESS_H
