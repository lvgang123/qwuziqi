#include "chesser.h"
#include "AI/aido.h"
#include "judgemodel.h"
#include "AI/aicore.h"

QScopedPointer<Chesser> Chesser::self;  //调用QScopedPointer智能指针格式

Chesser *Chesser::Instance()        //instance译为例子  创建实例
{
    if (self.isNull()) {
        static QMutex mutex;
        QMutexLocker locker(&mutex);    //创建互斥锁,出作用域时自动解锁销毁
        if (self.isNull()) {
            self.reset(new Chesser);
        }
    }

    return self.data();
}

Chesser::Chesser(QObject *parent) : QObject(parent)
{

}

void Chesser::start()
{
    //实例化定时器
    timer_AI = new QTimer(this);

    //绑定信号槽
    connect(timer_AI,&QTimer::timeout,
            [=](){
                    this->AIplayA();
                    this->AIplayB();
                    playingA = false;
                    playingB = false;
                });

    timer_AI->start(1);
}

void Chesser::stop()
{
    if(timer_AI->isActive())
        timer_AI->stop();
    timer_AI->deleteLater();

    qcout<<"time stop";
}

void Chesser::setConnInfo()
{

}

//黑AI
void Chesser::AIplayA()
{
    if(APP::WorkModle == 1)
        return;
    if(JudgeModel::Instance()->NextColour() == 1)
        return;
    if(APP::WorkModle == 0 && APP::AIColor == 1)
        return;
    if(playingA)
        return;
    playingA = true;

    AIDO::Instance(0)->setConnInfo(&APP::gameMapVec, APP::deepA, -1);
    AICore::Instance()->setScore(APP::scoreA);

    int row,col;
    int startime = clock();
    AIDO::Instance(0)->actionByAI(row ,col);
    int endtime = clock();
    //qcout << "AI-A计算用时:" << (double)(endtime - startime) * 1000 / CLOCKS_PER_SEC << "ms" ;
    emit actionByAI(row,col);
}

//白AI
void Chesser::AIplayB()
{
    if(APP::WorkModle == 1)
        return;
    if(JudgeModel::Instance()->NextColour() == -1)
        return;
    if(APP::WorkModle == 0 && APP::AIColor == -1)
        return;
    if(playingB){
        qcout<<"out0";
        return;
    }
    playingB = true;

    AIDO::Instance(1)->setConnInfo(&APP::gameMapVec, APP::deepB, 1);
    AICore::Instance()->setScore(APP::scoreB);
    //切换分值

    int row,col;
    int startime = clock();
    AIDO::Instance(1)->actionByAI(row ,col);
    int endtime = clock();
    //qcout << "AI-B计算用时:" << (double)(endtime - startime) * 1000 / CLOCKS_PER_SEC << "ms" ;
    emit actionByAI(row,col);
}

