#ifndef GAMESCENE_H
#define GAMESCENE_H

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
#include <QThread>
#include <resultscene.h>

class mainscene;

class gamescene : public QWidget
{
    Q_OBJECT

public:
    gamescene(QWidget *parent = 0);
    ~gamescene();
    void initscene();
    int songnumber,pre;
    vector<int> songlist;
    QTimer m_timer,startcount,bgtimer,endtimer;
    QTime tottime;
    int ptime;
    void playGame();
    void paintEvent(QPaintEvent *event);
    void updateStatus(int ntime);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    Track m_track[4];
    int checktype;
    int combo;
    int pausetime;
    int count[5];
    QPixmap checkimage[5][32];
    QPixmap track_bg;
    //gamescene * gs;
    //mainscene * ms;
    int bg_y,totcount;
    QLabel_C label[20],shadow[20];
    QLabel_C *plabel[4],*ptext[4],*pshadow[4];
    //QLabel_C ptext[4],pshadow[4];
    int ended,maxcombo;
    QPixmap background,pausebutton,pausebg,uileft,uiright,smallbase,bottomline;
    QGraphicsOpacityEffect opacityEffect[5];
    QMediaPlayer *player;
    int paused,started;
    int pause_seted;
    int gettime(){
        return tottime.elapsed()+pausetime;
    }
    void pause(){
        if(ended){
            return;
        }
        if(started){
            m_timer.stop();
            pausetime = gettime();
            player->pause();
        }
        //printf("%d\n",pausetime);
        paused = 1;
        if(!pause_seted){
            for(int i=0;i<=3;i++) plabel[i] = new QLabel_C,ptext[i] = new QLabel_C,pshadow[i] = new QLabel_C;
            setpix(plabel[0],pausebg,960,540);
            setpix(plabel[1],pausebutton,460,640);
            setpix(plabel[2],pausebutton,960,640);
            setpix(plabel[3],pausebutton,1460,640);
            setcolor(ptext[0],QColor(255,255,255));
            drawtext(ptext[0],QFont("GeosansLight", 45, false, false),960,510,"PAUSED");
            setcolor(ptext[1],QColor(255,255,255));
            drawtext(ptext[1],QFont("Noto Sans CJK SC Regular", 15, false, false),460,633,"返回");
            connect(ptext[1],&QLabel_C::clicked,this,&gamescene::return_to_play);
            connect(plabel[1],&QLabel_C::clicked,this,&gamescene::return_to_play);

            setcolor(ptext[2],QColor(255,255,255));
            drawtext(ptext[2],QFont("Noto Sans CJK SC Regular", 15, false, false),960,633,"重试");
            connect(ptext[2],&QLabel_C::clicked,this,&gamescene::retry);
            connect(plabel[2],&QLabel_C::clicked,this,&gamescene::retry);


            setcolor(ptext[3],QColor(255,255,255));
            drawtext(ptext[3],QFont("Noto Sans CJK SC Regular", 15, false, false),1460,633,"退出");
            connect(ptext[3],&QLabel_C::clicked,this,&gamescene::close_to_mainscene);
            connect(plabel[3],&QLabel_C::clicked,this,&gamescene::close_to_mainscene);
            pause_seted = 1;
        }else{
            for(int i=0;i<=3;i++){
                plabel[i]->show();
            }
            for(int i=0;i<=3;i++){
                ptext[i]->show();
            }
        }
    }
    void return_to_play(){
        for(int i=0;i<=3;i++){
            plabel[i]->hide();ptext[i]->hide();
        }
        if(started){
            player->play();
            tottime.restart();
            m_timer.start();
        }

        paused = 0;
    }
    void retry(){
        //printf("retried\n");
        for(int i=0;i<=3;i++){
            plabel[i]->hide();ptext[i]->hide();
        }
        //if(player != NULL) delete player;
        if(player) player->stop();
        //close_to_gamescene();
        close_to_gamescene();

//        gamescene* new_scene = new gamescene;
//        new_scene->songnumber = songnumber;
//        new_scene->initscene();

//        new_scene->playGame();
//        QTime dieTime = QTime::currentTime().addMSecs(100);
//        while( QTime::currentTime() < dieTime ) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
//        //delete this;
//        close();
    }
    //void back_to_main();
    void updatebg(int ntime);
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
    string getscore(){
        if(count[1]+count[2] == totcount){
            return "10000000";
        }else{
            int pscore = 10000000/totcount;
            int tscore = pscore*(count[1]+count[2]) + pscore*0.7*count[3];
            string now = to_string(tscore);
            while(now.length()<8) now = "0"+now;
            return now;
        }
    }
    int getintscore(){
        if(count[1]+count[2] == totcount){
            return 10000000;
        }else{
            int pscore = 10000000/totcount;
            int tscore = pscore*(count[1]+count[2]) + pscore*0.7*count[3];
            //string now = to_string(tscore);
            //while(now.length()<8) now = "0"+now;
            return tscore;
        }
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
    QPixmap shutter_l,shutter_r;
    QLabel_C shut[4];
    QTimer closetimer,closeupdater;
    QTimer opentimer,openupdater;
    void close_to_resultscene(){

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
            printf("%d\n%d\n",totcount,count[1]+count[2]+count[3]+count[4]);
            resultscene* new_scene = new resultscene;
            new_scene->openslot(songnumber,getintscore(),maxcombo,count[1]+count[2],count[3],count[4],pre,songlist);
            QTime dieTime = QTime::currentTime().addMSecs(5);
            while( QTime::currentTime() < dieTime ) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            //closecounter.stop();
            close();
        });
        closetimer.start();
        closeupdater.start();
    }
    void close_to_mainscene();
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
            new_scene->songnumber = songnumber;
            new_scene->pre = pre;
            new_scene->songlist = songlist;
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
    void open_with_shutter(){
        opentimer.setInterval(2000);
        openupdater.setInterval(1);
        //closecounter.start();
        connect(&openupdater,&QTimer::timeout,[=](){
            int rest = 2000-opentimer.remainingTime();
            if(rest>=500){
                double x_r = 1.0*(rest-500)/1500;
                setWindowOpacity(x_r*x_r);
            }

        });
        connect(&opentimer,&QTimer::timeout,[&](){
            shut[2].hide();
            shut[3].hide();
            opentimer.stop();
            openupdater.stop();

        });

        //setpix(&shut[2],shutter_l,shutter_l.width()/2,540);
        //setpix(&shut[3],shutter_r,1920-shutter_r.width()/2,540);
        show();
        opentimer.start();
        openupdater.start();
    }
public slots:
    void checkslot(int m_type);
};

#endif // GAMESCENE_H
