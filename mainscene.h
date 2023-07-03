#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <songselect.h>
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
#include <chapterselect.h>


using namespace std;
class mainscene : public basescene
{
    Q_OBJECT
public:
    mainscene(QWidget *parent = nullptr);
    void initscene();
    void paintEvent(QPaintEvent *event);
    void updateStatus(int ntime);
    //songselect *select_page;
    QPixmap up_button,mid_button,down_button;
    QPixmap text_world,midbut_shadow;
    void start();
    QLabel_C hlabel[2],hs[2];
    int first_help;
    void gethelp(){
        if(!first_help){
            first_help = 1;
            drawtext_left(&hlabel[0],QFont("Noto Sans CJK SC Regular",15,false,false),770,140,help_text[0]);
        }else drawtext_left(&hlabel[0],QFont("Noto Sans CJK SC Regular",15,false,false),770,140,help_text[rand()%help_tot]);

    }
    void close_to_chap(){

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
            chapterselect* new_scene = new chapterselect;
            new_scene->open_with_shutter(1);
            QTime dieTime = QTime::currentTime().addMSecs(5);
            while( QTime::currentTime() < dieTime ) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            //closecounter.stop();
            close();
        });
        closetimer.start();
        closeupdater.start();

    }
    void close_to_random_gamescene(){
        closetimer.setInterval(500);
        closeupdater.setInterval(1);
        //closecounter.start();
        connect(&closeupdater,&QTimer::timeout,[&](){
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
            new_scene->pre = -2;
            new_scene->songlist = {};
            new_scene->songnumber = rand()%song_size;
            new_scene->initscene();
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
            vector<int> vl= {2,7,13,15,35,39,27};
            new_scene->open_with_shutter(vl,-1);
            QTime dieTime = QTime::currentTime().addMSecs(5);
            while( QTime::currentTime() < dieTime ) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            //closecounter.stop();
            close();
        });
        closetimer.start();
        closeupdater.start();

    }
    void open_with_shutter(){

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

public slots:
    void chapter_select_slot();
};

#endif // MAINSCENE_H
