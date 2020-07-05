#include "aido.h"

unique_ptr<AIDO> AIDO::self[2];

AIDO *AIDO::Instance(const int num)        //instance译为例子  创建实例
{
    if (self[num] == NULL) {
        mutex mutex;
        mutex.lock();
        if (self[num] == NULL) {
            self[num].reset(new AIDO);    //将self指针指向new AppInit
        }
        mutex.unlock();
    }

    return self[num].get();
}

AIDO::AIDO()
{
}


AIDO::~AIDO()
{
}

void AIDO::start()
{

}

void AIDO::setConnInfo(vChess* inchess,int deep , const int AIcolor)
{
    this->LocalvChess = inchess;
    this->Localdeep = deep;
    this->LocalAICorlor = AIcolor;
}


void AIDO::actionByAI(int &row,int &col)
{
    //计算评分数组
    //this->calculateScore();
    //this->debuge_vchess(scoreMapVec);

    //选择落子点
    vChess tranvChess = *LocalvChess;
    CPoint result_piece = AIdeep::Instance()->Get_deepRsult(tranvChess,Localdeep,LocalAICorlor);
    row = result_piece.y;
    col = result_piece.x;
}
