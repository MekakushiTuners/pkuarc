#include "track.h"
#include "config.h"
#include "qpainter.h"

Track::Track(QObject *parent)
    : QObject(parent)
{
    m_X = GAME_WIDTH*0.5;
    m_Y = GAME_HEIGHT*0.5;
    pos1 = pos2 = 0;
}
Track::~Track(){

}
void Track::push_button(Button a){
    nex_but.push_back(a);
}
void Track::uptateStatus(int ntime){
    //printf("%d\n",ntime);
    while(pos1 < ontrack_but.size()){
        Button fr = ontrack_but[pos1];
        if(fr.endtime <= ntime - MISS_DELAY){
            pos1++;
            emit checksignal(4);
        }else break;
    }
    for(int i = pos1; i < ontrack_but.size(); i++){
        ontrack_but[i].fall(ntime);
    }
    while(pos2 < nex_but.size()){
        Button fr = nex_but[pos2];
        if(fr.m_time <= ntime + (100+CHECKLINE_POS) /FALL_SPEED + TIME_EPS){
            fr.fall(ntime);fr.m_X = m_X;
            ontrack_but.push_back(fr);
            pos2++;
        }else break;
    }
}
void Track::onpressed(int ntime){
    if(pos1 < ontrack_but.size()){
        Button fr = ontrack_but[pos1];
        int dir = abs(ntime - fr.m_time);
        if(dir <= PERFECT_DELAY){
            pos1++;
            emit checksignal(1);
        }else if(dir <= GREAT_DELAY){
            pos1++;
            emit checksignal(2);
        }else if(dir <= GOOD_DELAY){
            pos1++;
            emit checksignal(3);
        }else if(dir <= MISS_DELAY){
            pos1++;
            emit checksignal(4);
        }
    }
}
void Track::drawtrack(QPainter &painter){
    for(int i = pos1; i < ontrack_but.size(); i++){
        painter.drawPixmap(ontrack_but[i].m_X, ontrack_but[i].m_Y, ontrack_but[i].m_button);
    }
}
void Track::setposition(int x,int y){
    m_X = x;
    m_Y = y;
}
