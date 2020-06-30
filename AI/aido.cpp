#include "aido.h"
#include "mutex"

unique_ptr<AIDO> AIDO::self;

AIDO *AIDO::Instance()        //instance译为例子  创建实例
{
    if (self == NULL) {
        mutex mutex;
        mutex.lock();
        if (self == NULL) {
            self.reset(new AIDO);    //将self指针指向new AppInit
        }
        mutex.unlock();
    }

    return self.get();
}

AIDO::AIDO()
{
}


AIDO::~AIDO()
{
}

string AIDO::test()
{
    (*LcoalvChess)[0][0] = 1;
    string out="AI model test";
    return out;
}

void AIDO::setConnInfo(vChess* inchess)
{
    this->LcoalvChess = inchess;
    cout<<LcoalvChess<<"\n";
}
