#include "chess.h"
#include "judgemodel.h"
#include "AI/aido.h"
#include "frmshow/show.h"
#include "chesser.h"

QScopedPointer<Chess> Chess::self;  //调用QScopedPointer智能指针格式

Chess *Chess::Instance()        //instance译为例子  创建实例
{
    if (self.isNull()) {
        static QMutex mutex;
        QMutexLocker locker(&mutex);    //创建互斥锁,出作用域时自动解锁销毁
        if (self.isNull()) {
            self.reset(new Chess);    //将self指针指向new AppInit
        }
    }

    return self.data();
}

Chess::Chess(QObject *parent) : QObject(parent)
{

}

void Chess::start()
{
}

void Chess::setConnInfo(vChess* inchess)
{
    LcoalvChess = inchess;
}

void Chess::actionAddPiece(int row ,int col)
{
    int startime = clock();
    //判断行、列是够越界
    if(row >= LcoalvChess->size()){
        qcout<<"棋盘输入行越界";
        return;
    }
    if(col >= (*LcoalvChess)[row].size()){
        qcout<<"棋盘输入列越界";
        return;
    }

    //判断该处是否有棋子
    if((*LcoalvChess)[row][col] != 0){
        qcout<<"该处已有棋子";
        return;
    }


    int now_piece = JudgeModel::Instance()->NextColour();
    {
    static QMutex mutex;
    QMutexLocker locker(&mutex);    //创建互斥锁,出作用域时自动解锁销毁
    (*LcoalvChess)[row][col] = now_piece;
    }
    //棋盘容器添加后更新主界面
    APP::Show_waite = true;
    emit UpdateShow();
    QHelper::wait_false(APP::Show_waite);

    //棋局判断
    //对胜负进行判断
    if(JudgeModel::Instance()->isWin(row,col))
        emit GameOver(now_piece);
    else if(JudgeModel::Instance()->isDeadGame())
        emit GameOver(0);

    //计算平均用时，千次
    int endtime = clock();
    count_record++;
    time_record = time_record + (double)(endtime - startime) * 1000 / CLOCKS_PER_SEC;
    //qcout<<time_record;
    if(count_record >= 1000){
        qcout<<"（棋盘增加及界面绘制）千次输入平均时间:"<<time_record/count_record<<"ms";
        count_record = 0;
        time_record = 0;
    }
}
