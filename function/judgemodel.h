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

private slots:


public slots:
    //模块启动函数
    void start();
};

#endif // JUDGEMODEL_H
