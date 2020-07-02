#include <QApplication>
#include "function/appinit.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AppInit::Instance()->start();

    return a.exec();
}
