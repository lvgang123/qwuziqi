#ifndef SHOW_H
#define SHOW_H

/**
 * 界面绘制模块 整理:lvgang 2020-6-30
 * 1.qt中Mainwindow为最上层部件，无法用一般方法进行智能指针传递，本处采用普通指针进行调用该模块
 */

#include <qmainwindow.h>
#include "help/head.h"
#include <QObject>

class Show : public QMainWindow
{
    Q_OBJECT
public:
    static Show *Instance();
    explicit Show(QWidget *parent = 0);
    ~Show();

private:
    static Show* self;

    vChess* LcoalvChess;
    int clickPosRow, clickPosCol; // 存储将点击的位置

protected:
    // 绘制
    void paintEvent(QPaintEvent *event);
    // 监听鼠标移动情况，方便落子
    void mouseMoveEvent(QMouseEvent *event);
    // 实际落子
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    //添加菜单
    void addMenu();

signals:
    //人工落子完成
    void actionByPerson(int row ,int col);


public slots:
    //模块启动函数
    void start();
    //模块设定
    void setConnInfo(vChess* inchess);
    //重绘界面接口
    void UpdateShow();
    //重置游戏
    void restart();
    //游戏结束槽函数
    void GameOver(int index);
};

#endif // SHOW_H
