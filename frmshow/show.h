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
    int clickPosRow, clickPosCol;                   // 存储鼠标点击的位置
    int winblack = 0;
    int winwhite = 0;

protected:
    void paintEvent(QPaintEvent *event);            // 更新绘制整个界面
    void mouseMoveEvent(QMouseEvent *event);        // 监听鼠标移动情况，方便落子
    void mouseReleaseEvent(QMouseEvent *event);     // 实际落子位置
    void closeEvent(QCloseEvent *event);            //窗口关闭时间

private slots:
    void addMenu();                                 //添加菜单

signals:
    void actionByPerson(int row ,int col);          //人工落子完成

public slots:
    void start();                                   //模块启动函数
    void setConnInfo(vChess* inchess);              //模块设定
    void UpdateShow();                              //重绘界面接口槽函数
    void restart();                                 //重置游戏
    void GameOver(int index);                       //游戏结束槽函数
    void actionByshow(int row ,int col);
};

#endif // SHOW_H
