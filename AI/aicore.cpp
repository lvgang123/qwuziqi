#include "aicore.h"

unique_ptr<AICore> AICore::self;

AICore *AICore::Instance()        //instance译为例子  创建实例
{
    if (self == NULL) {
        mutex mutex;
        mutex.lock();
        if (self == NULL) {
            self.reset(new AICore);    //将self指针指向new AppInit
        }
        mutex.unlock();
    }

    return self.get();
}

AICore::AICore()
{
}


AICore::~AICore()
{
}

void AICore::start()
{

}

void AICore::setConnInfo()
{

}
