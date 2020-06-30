#include "appinit.h"

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

}
