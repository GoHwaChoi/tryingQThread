#include "ScratchQThread.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ScratchQThread w;
    w.show();
    return a.exec();
}
