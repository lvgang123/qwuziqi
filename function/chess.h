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

private slots:


public slots:
    //模块启动函数
    void start();
};

#endif // CHESS_H
