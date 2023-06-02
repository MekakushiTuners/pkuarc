#include "track.h"
#include "config.h"
#include "qpainter.h"
#include<vector>
using namespace std;
Track::Track(QObject *parent)
    : QObject(parent)
{
    //m_X = GAME_WIDTH*0.5;
    //m_Y = GAME_HEIGHT*0.5;
    pos1 = pos2 = pressed = 0;
}
Track::~Track(){

}
void Track::push_button(Button a){
    nex_but.push_back(a);
}
void Track::uptateStatus(int ntime){
    //printf("%d\n",ntime);
    while(pos1 < ontrack_but.size()){
        Button &fr = ontrack_but[pos1];
        if(fr.endtime == fr.m_time){ // single button
            if(fr.m_time <= ntime - MISS_DELAY){
                pos1++;
                emit checksignal(4);
            }else break;
        }else{
            //printf("%d %d\n",fr.pdtime.size(),fr.pdpos);
            while(fr.pdpos < fr.pdtime.size()){
                 if(fr.pdtime[fr.pdpos] <= ntime + PERFECT_DELAY && pressed == 1){
                        //printf("%d\n",fr.pdtime[fr.pdpos]);
                        emit checksignal(1);
                        //printf("%d %d %d\n",ntime,fr.pdpos,pos1);
                        fr.pdpos++;
                 }else if(fr.pdtime[fr.pdpos] <= ntime - PERFECT_DELAY && !pressed){
                        //printf("%d\n",fr.pdtime[fr.pdpos]);
                        emit checksignal(4);
                        fr.pdpos++;
                 }else break;
            }
            if(fr.endtime <= ntime - PERFECT_DELAY - 10){
                pos1++;/*if(fr.pdpos != fr.pdtime.size()){
                    printf("ntime:%d endtime:%d,checktime:%d fr.pressed:%d\n",ntime,fr.endtime,fr.pdtime[fr.pdpos],fr.pressed);
                }*/
            }
            break;
        }
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

            if(fr.endtime == fr.m_time){
                //ontrack_but[pos1].first_pressed = 1;
                if(dir <= PERFECT_DELAY){
                    emit checksignal(1);
                }else if(dir <= GREAT_DELAY){
                    emit checksignal(2);
                }else if(dir <= GOOD_DELAY){
                    emit checksignal(3);
                }else if(dir <= MISS_DELAY){
                    emit checksignal(4);
                }//else ontrack_but[pos1].first_pressed = 0;
            }


            int flg = (dir <= MISS_DELAY);

            // 长条的首次判定在这里发出信号

            if(fr.m_time == fr.endtime){
                if(flg) pos1++;
            }else{
                //ontrack_but[pos1].pressed = 1;
                pressed = 1;
            }

    }
}
void Track::onreleased(int ntime){
    pressed = 0;

//    if(pos1 < ontrack_but.size()){
//        Button fr = ontrack_but[pos1];
//        int dir = abs(ntime - fr.m_time);
//        if(ntime < fr.m_time || fr.m_time == fr.endtime) return;

//    }
}
void Track::drawtrack(QPainter &painter){
    for(int i = pos1; i < ontrack_but.size(); i++){
        if(ontrack_but[i].m_time == ontrack_but[i].endtime){
            drawpix_inmiddle(painter,ontrack_but[i].m_button,ontrack_but[i].m_X,ontrack_but[i].m_Y);
        }else{
            int timdir = ontrack_but[i].endtime - ontrack_but[i].m_time;
            int pixh = ontrack_but[i].m_button.height();
            int paintcnt = timdir * FALL_SPEED / pixh + ((int)(timdir * FALL_SPEED)%pixh>0);
            int px = ontrack_but[i].m_X,py = ontrack_but[i].m_Y;
            for(int j=1;j<=paintcnt;j++){
                drawpix_inmiddle(painter,ontrack_but[i].m_button,px,py);
                py-=pixh;
            }
        }

    }
}
void Track::setposition(int x,int y){
    m_X = x;
    m_Y = y;
}
