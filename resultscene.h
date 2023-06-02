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

class mainscene;

class resultscene : public QWidget
{
    Q_OBJECT

public:
    resultscene(QWidget *parent = 0);
    ~resultscene();
    void initscene();
    int songnumber,maxrecall;
    QTimer m_timer;
    QTime tottime;
    QPixmap scoresection,res_banner;
    QPixmap pd_a,pd_aa,pd_b,pd_c,pd_d,pd_ex,pd_explus;
    QPixmap background,ratingbox,midsquare,charabox;
    QPixmap chara,topbar,setbox,seticon,membox,base,backbutton,completebar;
    QLabel_C label[20],tex[20],sha[20];
    QGraphicsOpacityEffect* opacityEffect[5];
    QLabel_C pixlabel[20];
    int y_bg,y_cha,score,pure,far,lost;
    void paintEvent(QPaintEvent *event);
    void updateStatus(int ntime);
    //void keyPressEvent(QKeyEvent *event);
    //void keyReleaseEvent(QKeyEvent *event);
    void backtomain();
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
    void drawtext(QLabel_C *label,QFont font,int x,int y,string s){
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
    void drawtext_with_shadow(QLabel_C *label,QLabel_C *shadow,QFont font,int x,int y,string s){
        setcolor(label,QColor(255,255,255));
        setcolor(shadow,QColor(0, 0, 0));
        drawtext(shadow,font,x+2,y+2,s);
        drawtext(label,font,x,y,s);
    }
    void drawtext_left_with_shadow(QLabel_C *label,QLabel_C *shadow,QFont font,int x,int y,string s){
        setcolor(label,QColor(255,255,255));
        setcolor(shadow,QColor(0, 0, 0));
        drawtext_left(shadow,font,x+2,y+2,s);
        drawtext_left(label,font,x,y,s);
    }
    void drawtext_left(QLabel_C *label,QFont font,int x,int y,string s){
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
    void openslot(int num,int sc,int mx,int pr,int fr,int lo,int PRE,vector<int> sl);
    QPixmap shutter_l,shutter_r;
    QLabel_C shut[4];
    QTimer closetimer,closeupdater;
    void close_to_mainscene();
    QTimer opentimer,openupdater;
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
