#ifndef songselect_H
#define songselect_H

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
#include <basescene.h>


using namespace std;

class mainscene;

class songselect : public basescene
{
    Q_OBJECT
public:
    songselect(QWidget *parent = nullptr);
    void initscene();
    void paintEvent(QPaintEvent *event);
    //void updateStatus(int ntime);
    QPixmap song_cell_corner_2,song_cell_corner_light,song_cell_name_underlay,song_cell_right,song_cell_selected_piece,text_start;
    QPixmap song_currentpack,new_badge,jacket_glow,backbutton;
    QPixmap difficulty_selector_0,difficulty_selector_1,difficulty_selector_2,difficulty_selector_3_locked,song_score_tab,text_shadow,scorelist_shadow;
    QLabel_C songtext[10][2];
    QLabel_C shsongtext[10][2];
    QLabel_C songlabel[7][7],slabel[20];
    vector<int> songlist;
    int nowsong,nowindex;
    void start();
    void setsong(int id,int x,int y){
        QPixmap smallpix;
        smallpix.load(songs[songlist[id]].base);
        scaling_pix(smallpix,0.5);
        setpix_withmask(&songlabel[id][4],smallpix,x-60,y+20);
    }
    void close_to_mainscene();
    void close_to_chap();
    void close_to_gamescene(){
        closetimer.setInterval(500);
        closeupdater.setInterval(1);
        //closecounter.start();
        connect(&closeupdater,&QTimer::timeout,[=](){
            int rest = closetimer.remainingTime();
            if(rest>100){
                double x_r = 1.0*(rest-100)/400;
                setWindowOpacity(x_r*x_r);
            }

        });
        connect(&closetimer,&QTimer::timeout,[&](){
            closetimer.stop();
            closeupdater.stop();
            gamescene* new_scene = new gamescene;
            new_scene->songnumber = nowsong;
            new_scene->initscene();
            new_scene->pre = pre;
            new_scene->songlist = songlist;
            //new_scene->show();
            new_scene->open_with_shutter();
            new_scene->playGame();
            QTime dieTime = QTime::currentTime().addMSecs(5);
            while( QTime::currentTime() < dieTime ) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            //closecounter.stop();
            close();
        });
        closetimer.start();
        closeupdater.start();

    }
    int pre;
    void open_with_shutter(vector<int> sl,int pr){
        pre = pr;
        songlist = sl;
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

#endif // songselect_H
