#ifndef chapterselect_H
#define chapterselect_H

#include <gamescene.h>
#include <QWidget>
#include <config.h>
#include <QTime>
#include <qtimer.h>
#include <qpainter.h>
#include "qpixmap.h"
#include "iostream"
#include "QLabel"
#include "QFontMetrics"
#include "qtimer.h"
#include "QGraphicsOpacityEffect"
#include "QMouseEvent"
#include "utils.h"
#include <QBitmap>
#include <vector>
#include <qsound.h>
#include <songselect.h>
#include <basescene.h>

using namespace std;

class mainscene;

class chapterselect : public basescene
{
    Q_OBJECT
public:
    chapterselect(QWidget *parent = nullptr);
    void initscene();
    void paintEvent(QPaintEvent *event);
    //void updateStatus(int ntime);
    //gamescene *game;
    //mainscene* ms;
    QPixmap backbutton,title_back,arrow_l,arrow_r;
    QPixmap bg[10],title[10],square[10];
    QLabel_C songtext[10][2];
    QLabel_C shsongtext[10][2];
    QLabel_C songlabel[7][7];
    vector<int> songlist[10];
    int nowchap;
    void start();
    void go_left(){
        nowchap--;nowchap<=0?nowchap++:0;
        update();
    }
    void go_right(){
        nowchap++;nowchap>8?nowchap--:0;
        update();
    }
    void setsong(int id,int x,int y){
        QPixmap smallpix;
        smallpix.load(songs[id].base);
        scaling_pix(smallpix,0.5);
        setpix_withmask(&songlabel[id][4],smallpix,x-60,y+20);
    }
    void close_to_mainscene();
    void close_to_songselect(){

        closetimer.setInterval(500);
        closeupdater.setInterval(1);
        //closecounter.start();
        connect(&closeupdater,&QTimer::timeout,[&](){
            int rest = closetimer.remainingTime();
            if(rest>100){
                double x_r = 1.0*(rest-100)/400;
                int nxl = shutter_l.width()/2-(x_r*x_r)*shutter_l.width();
                int nxr = 1920-shutter_r.width()/2+(x_r*x_r)*shutter_r.width();
                setpix(&shut[0],shutter_l,nxl,540);
                setpix(&shut[1],shutter_r,nxr,540);
            }

        });
        connect(&closetimer,&QTimer::timeout,[&](){
            closetimer.stop();
            closeupdater.stop();
            songselect* new_scene = new songselect;
            new_scene->open_with_shutter(songlist[nowchap],nowchap);
            QTime dieTime = QTime::currentTime().addMSecs(5);
            while( QTime::currentTime() < dieTime ) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            //closecounter.stop();
            close();
        });
        closetimer.start();
        closeupdater.start();
    }
    void open_with_shutter(int np){
        nowchap = np;
        initscene();
        opentimer.setInterval(500);
        openupdater.setInterval(1);
        //closecounter.start();
        connect(&openupdater,&QTimer::timeout,[&](){
            int rest = 500-opentimer.remainingTime();
            if(rest>=100){
                double x_r = 1.0*(rest-100)/400;
                int nxl = shutter_l.width()/2-(x_r*x_r)*shutter_l.width();
                int nxr = 1920-shutter_r.width()/2+(x_r*x_r)*shutter_r.width();
                setpix(&shut[2],shutter_l,nxl,540);
                setpix(&shut[3],shutter_r,nxr,540);
            }

        });
        connect(&opentimer,&QTimer::timeout,[&](){
            shut[2].hide();
            shut[3].hide();
            opentimer.stop();
            openupdater.stop();

        });

        setpix(&shut[2],shutter_l,shutter_l.width()/2,540);
        setpix(&shut[3],shutter_r,1920-shutter_r.width()/2,540);
        show();
        opentimer.start();
        openupdater.start();
    }
signals:
    //void playsignal(int sn);
public slots:
    //void openslot();
    void backtomain();
};

#endif // chapterselect_H
