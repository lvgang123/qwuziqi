#include <QApplication>
#include "function/appinit.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    AppInit::Instance()->start();

    qcout<<&APP::gameMapVec;

    if(APP::gameMapVec.size()>0 && APP::gameMapVec[0].size()>0)
        qcout<<APP::gameMapVec.at(0).at(0);

    return a.exec();
}
