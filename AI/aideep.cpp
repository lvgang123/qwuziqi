#include "aideep.h"

unique_ptr<AIdeep> AIdeep::self;

AIdeep *AIdeep::Instance()        //instance译为例子  创建实例
{
    if (self == NULL) {
        mutex mutex;
        mutex.lock();
        if (self == NULL) {
            self.reset(new AIdeep);    //将self指针指向new AppInit
        }
        mutex.unlock();
    }

    return self.get();
}

AIdeep::AIdeep()
{
}


AIdeep::~AIdeep()
{
}

void AIdeep::start()
{

}

void AIdeep::setConnInfo()
{

}
