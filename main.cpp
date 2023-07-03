//#include "chapterselect.h"
#include<introscene.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    introscene w;
    //resultscene w;

    //chapterselect *w = new chapterselect;
    w.show();
    //w.openslot(3,9850000,500,400,50,50);
//    w.playGame();
    // w.playGame();
    return a.exec();
}
