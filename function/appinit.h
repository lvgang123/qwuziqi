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


public slots:
    //程序函数
    void start();
};

#endif // APPINIT_H
