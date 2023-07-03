#ifndef RESULTSCENE_H
#define RESULTSCENE_H


#include <QMainWindow>
#include <qtimer.h>
#include <button.h>
#include <track.h>
#include <QTime>
#include <QLabel>
#include <utils.h>
#include <QGraphicsOpacityEffect>
#include <qmediaplayer.h>
#include <QCoreApplication>
#include <basescene.h>

class mainscene;

class resultscene : public basescene
{
    Q_OBJECT

public:
    resultscene(QWidget *parent = 0);
    ~resultscene();
    void initscene();
    int songnumber,maxrecall;
    QPixmap scoresection,res_banner;
    QPixmap pd_a,pd_aa,pd_b,pd_c,pd_d,pd_ex,pd_explus;
    QPixmap backbutton,completebar,base;
    QLabel_C label[20],tex[20],sha[20];
    QGraphicsOpacityEffect* opacityEffect[5];
    QLabel_C pixlabel[20];
    int score,pure,far,lost;
    void paintEvent(QPaintEvent *event);
    void updateStatus(int ntime);
    //void keyPressEvent(QKeyEvent *event);
    //void keyReleaseEvent(QKeyEvent *event);
    void backtomain();
    void openslot(int num,int sc,int mx,int pr,int fr,int lo,int PRE,vector<int> sl);
    void close_to_mainscene();
    int pre;vector<int> songlist;
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
public slots:
};

#endif // RESULTSCENE_H
