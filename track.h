#ifndef TRACK_H
#define TRACK_H
#include<vector>
#include<button.h>
#include "qpainter.h"
#include "qpixmap.h"
using namespace std;

class Track:public QObject
{
    Q_OBJECT

public:
    Track(QObject *parent = 0);
    ~Track();
    int m_X,m_Y;
    vector<Button> ontrack_but;
    vector<Button> nex_but;
    int pos1,pos2,pressed;
    void clear(){
        pos1 = pos2 = 0;
        ontrack_but.clear();
        nex_but.clear();
    }
    void push_button(Button a);
    void uptateStatus(int ntime);
    void drawtrack(QPainter &painter);
    void setposition(int x,int y);
    void onpressed(int ntime);
    void onreleased(int ntime);
    void drawpix_inmiddle(QPainter &painter,QPixmap pix,int x,int y){
        painter.drawPixmap(x - pix.width()/2, y - pix.height()/2, pix);
    }
    void draw_background(QPainter &painter,QPixmap pix){
        double l = std::min(1920.0 / pix.width(), 1080.0 / pix.height());
        pix = pix.scaled(ceil(l*pix.width()),ceil(l*pix.height()),Qt::KeepAspectRatio);
        painter.drawPixmap(960 - pix.width()/2,540 - pix.height()/2, pix);
    }
    int ended(){
        return pos2 == nex_but.size()&&pos1 == ontrack_but.size();
    }
signals:
    void checksignal(int m_type);
};

#endif // TRACK_H
