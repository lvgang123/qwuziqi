#include "appinit.h"
#include "ai/aido.h"
#include "frmshow/show.h"
#include "chess.h"
#include "judgemodel.h"

QScopedPointer<AppInit> AppInit::self;  //调用QScopedPointer智能指针格式

AppInit *AppInit::Instance()        //instance译为例子  创建实例
{
    if (self.isNull()) {
        static QMutex mutex;
        QMutexLocker locker(&mutex);    //创建互斥锁,出作用域时自动解锁销毁
        if (self.isNull()) {
            self.reset(new AppInit);    //将self指针指向new AppInit
        }
    }

    return self.data();
}

AppInit::AppInit(QObject *parent) : QObject(parent)
{

}

void AppInit::start()
{
    //可以通过指针的形式将棋盘传递进每一个功能模块，使模块解耦合
    APP::initchess();            //对棋盘进行初始化，否则出现野指针

    this->initShow();
    this->initChess();
    this->initJudge();
    this->initAIdo();
}

void AppInit::initShow()
{
    Show::Instance()->setConnInfo(&APP::gameMapVec);
    Show::Instance()->start();
    connect(Chess::Instance(),SIGNAL(UpdateShow()), Show::Instance(), SLOT(UpdateShow()));
    connect(Chess::Instance(),SIGNAL(GameOver(int)), Show::Instance(), SLOT(GameOver(int)));
}

void AppInit::initChess()
{
    Chess::Instance()->setConnInfo(&APP::gameMapVec);
    Chess::Instance()->start();
    connect(Show::Instance(),SIGNAL(actionByPerson(int,int)), Chess::Instance(), SLOT(actionAddPiece(int,int)));
}

void AppInit::initJudge()
{
    JudgeModel::Instance()->setConnInfo(&APP::gameMapVec);
    JudgeModel::Instance()->start();
}

void AppInit::initAIdo()
{
    AIDO::Instance()->setConnInfo(&APP::gameMapVec);
    AIDO::Instance()->start();
}
