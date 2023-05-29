#ifndef introscene_H
#define introscene_H

#include <QWidget>
#include <config.h>
#include <QTime>
#include <qtimer.h>
#include <mainscene.h>
#include <QMouseEvent>

class introscene : public QWidget
{
    Q_OBJECT

public:
    introscene(QWidget *parent = nullptr);
    ~introscene();
    void initscene();
    void startgame();
    QTime tottime;
    QTimer m_timer;

    int op_finished;
    int bg_y;
    int lp; // 0 - 255
    double tp; // 0 - 1
    QPixmap background;
    QPixmap game_title_icon;
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void updateStatus(int ntime);
    void setpix(QLabel_C *label,QPixmap pix,int x,int y){
        label->setParent(this);
        label->setPixmap(pix);
        label->move(x-pix.width()/2,y-pix.height()/2);
        label->show();
    }
    void scaling_pix(QPixmap &pix,double l){
        pix = pix.scaled(l*pix.width(),l*pix.height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    }

    QPixmap shutter_l,shutter_r;
    QLabel_C shut[2];
    QTimer closetimer,closeupdater;

    template<class T>
    void close_with_shutter(){

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
            T* new_scene = new T;
            new_scene->open_with_shutter();
            QTime dieTime = QTime::currentTime().addMSecs(5);
            while( QTime::currentTime() < dieTime ) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            //closecounter.stop();
            close();
        });
        closetimer.start();
        closeupdater.start();

    }
    //mainscene* new_game;

signals:
    //void gamesignal();
    //void closesignal();
};

#endif // introscene_H
