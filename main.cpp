#include "introscene.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    introscene w;
    w.show();
//    w.playGame();
    // w.playGame();
    return a.exec();
}
