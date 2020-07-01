#include <QApplication>
#include "ai/aido.h"
#include <iostream>
#include "frmshow/show.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //可以通过指针的形式将棋盘传递进每一个功能模块，使模块解耦合
    APP::initchess();            //对棋盘进行初始化，否则出现野指针

    AIDO::Instance()->setConnInfo(&APP::gameMapVec);
    std::cout << AIDO::Instance()->test() << "\n";

    Show::Instance()->setConnInfo(&APP::gameMapVec);
    Show::Instance()->start();

    qcout<<&APP::gameMapVec;

    if(APP::gameMapVec.size()>0 && APP::gameMapVec[0].size()>0)
        qcout<<APP::gameMapVec.at(0).at(0);

    return a.exec();
}
