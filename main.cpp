#include "mainscene.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainscene w;
    w.show();
    w.playGame();
    return a.exec();
}
