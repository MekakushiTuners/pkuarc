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


using namespace std;

class mainscene;

class chapterselect : public QWidget
{
    Q_OBJECT
public:
    chapterselect(QWidget *parent = nullptr);
    void initscene();
    void paintEvent(QPaintEvent *event);
    //void updateStatus(int ntime);
    //gamescene *game;
    //mainscene* ms;
    QPixmap background,ratingbox,charabox;
    QPixmap text_world,midbut_shadow,topbar,setbox,seticon,membox;
    QPixmap backbutton,title_back,arrow_l,arrow_r;
    QPixmap bg[10],title[10],square[10];
    QLabel_C label[20],songtext[10][2];
    QLabel_C slabel[20],shsongtext[10][2];
    QLabel_C pixlabel[20],songlabel[7][7];
    QTime tottime;
    QTimer m_timer;
    QGraphicsOpacityEffect opacityEffect[5];
    vector<int> songlist[10];
    int y_bg;
    int y_cha;
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
    void setcolor(QLabel *label,QColor _color){
        QRgb textRGB = qRgb(_color.red(),_color.green(),_color.blue());
        QString textRGBStr = QString::number(textRGB,16);
        QString colorStr = "color:#"+textRGBStr;
        label->setStyleSheet(colorStr);
    }
    void drawpix_inmiddle(QPainter &painter,QPixmap pix,int x,int y){
        painter.drawPixmap(x - pix.width()/2, y - pix.height()/2, pix);
    }
    void draw_background(QPainter &painter,QPixmap pix){
        double l = std::min(1920.0 / pix.width(), 1080.0 / pix.height());
        pix = pix.scaled(ceil(l*pix.width()),ceil(l*pix.height()),Qt::KeepAspectRatio);
        painter.drawPixmap(960 - pix.width()/2,540 - pix.height()/2, pix);
    }
    void scaling_pix(QPixmap &pix,double l){
        pix = pix.scaled(l*pix.width(),l*pix.height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    }

    void setpix(QLabel_C *label,QPixmap pix,int x,int y){
        label->setParent(this);
        label->setPixmap(pix);
        label->move(x-pix.width()/2,y-pix.height()/2);
        label->adjustSize();
        label->show();
    }
    void setpix_withmask(QLabel_C *label,QPixmap pix,int x,int y){
        label->setParent(this);
        label->setPixmap(pix);
        label->move(x-pix.width()/2,y-pix.height()/2);
//        QBitmap mask;
//        mask.fill(Qt::color0); // 设置初始遮罩颜色
//        QPainter painter(&mask);
//        painter.fillRect(x, y, 50, 50, Qt::color1); // 设置矩形遮罩区域
//        painter.end();
        label->setMask(QRect(0,72,300,102));
        label->show();
    }
    void drawtext(QLabel *label,QFont font,int x,int y,string s){
        label->setParent(this);
        label->setText(QString::fromStdString(s));
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        QFontMetrics fm(font);
        QString a = QString::fromStdString(s);
        int width = fm.width(a);
        int height = fm.ascent()+fm.descent();
        label->adjustSize();
        label->move(x-width/2,y-height/2);
        label->show();
    }
    void drawtext_with_shadow(QLabel *label,QLabel *shadow,QFont font,int x,int y,string s){
        setcolor(label,QColor(255,255,255));
        setcolor(shadow,QColor(0, 0, 0));
        drawtext(shadow,font,x+2,y+2,s);
        drawtext(label,font,x,y,s);
    }
    void drawtext_left_with_shadow(QLabel *label,QLabel *shadow,QFont font,int x,int y,string s){
        setcolor(label,QColor(255,255,255));
        setcolor(shadow,QColor(0, 0, 0));
        drawtext_left(shadow,font,x+2,y+2,s);
        drawtext_left(label,font,x,y,s);
    }
    void drawtext_left(QLabel *label,QFont font,int x,int y,string s){
        label->setParent(this);
        label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        //slabel.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        label->setText(QString::fromStdString(s));
        label->setFont(font);
        //label.setAlignment(Qt::AlignCenter);
        QFontMetrics fm(font);
        QString a = QString::fromStdString(s);
        //int width = fm.width(a);
        int height = fm.ascent()+fm.descent();
        label->adjustSize();
        label->move(x,y-height/2);
        label->show();
    }
    QPixmap set_bg,icon_plus,icon_minus,ret_button;
    QLabel_C setlabel[10],setshadow[10];
    int first_seted;
    void setnum(){
        int d1 = (int)floor(FALL_SPEED)-1;
        int d2 = (int)floor(FALL_SPEED*10)-(d1+1)*10;
        drawtext_with_shadow(&setlabel[2],&setshadow[2],QFont("GeosansLight",35,false,false),660,530,to_string(d1)+"."+to_string(d2));
        drawtext_with_shadow(&setlabel[3],&setshadow[3],QFont("GeosansLight",35,false,false),1260,530,to_string(WAIT_TIME-ORI_WAIT_TIME));
    }
    void opensettings(){
        if(!first_seted){
            first_seted = 1;
        }else{
            for(int i=0;i<=8;i++){
                setlabel[i].show();
            }
            for(int i=2;i<=3;i++){
                setshadow[i].show();
            }
            return;
        }
        setpix(&setlabel[0],set_bg,960,540);
        setpix(&setlabel[1],ret_button,960,640);
        setcolor(&setlabel[8],QColor(255,255,255));
        drawtext(&setlabel[8],QFont("Noto Sans CJK SC Regular",15,false,false),955,635,"完成");
        setnum();
        setpix(&setlabel[4],icon_minus,560,530);
        setpix(&setlabel[5],icon_plus,760,530);
        connect(&setlabel[4],&QLabel_C::clicked,[=](){
            if(FALL_SPEED>1.2) FALL_SPEED-=0.1;
            setnum();
        });
        connect(&setlabel[5],&QLabel_C::clicked,[=](){
            if(FALL_SPEED<4) FALL_SPEED+=0.1;
            setnum();
        });


        setpix(&setlabel[6],icon_minus,1160,530);
        setpix(&setlabel[7],icon_plus,1360,530);
        connect(&setlabel[6],&QLabel_C::clicked,[=](){
            if(WAIT_TIME>ORI_WAIT_TIME-999) WAIT_TIME--;
            setnum();
        });
        connect(&setlabel[7],&QLabel_C::clicked,[=](){
            if(WAIT_TIME<ORI_WAIT_TIME+999) WAIT_TIME++;
            setnum();
        });
        connect(&setlabel[1],&QLabel_C::clicked,[=]{
            for(int i=0;i<=8;i++){
                setlabel[i].hide();
            }
            for(int i=2;i<=3;i++){
                setshadow[i].hide();
            }
        });
        connect(&setlabel[8],&QLabel_C::clicked,[=]{
            for(int i=0;i<=8;i++){
                setlabel[i].hide();
            }
            for(int i=2;i<=3;i++){
                setshadow[i].hide();
            }
        });
    }
    QPixmap shutter_l,shutter_r;
    QLabel_C shut[4];
    QTimer closetimer,closeupdater;
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
    QTimer opentimer,openupdater;
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
