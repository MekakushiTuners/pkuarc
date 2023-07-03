#include "resultscene.h"
#include "config.h"
#include "qicon.h"
#include "qpainter.h"
#include "qtimer.h"
#include "QKeyEvent"
#include <QPainter>
#include <QFont>
#include <QRectF>
#include <QFontMetrics>
#include <QString>
#include <QMediaPlayer>
#include <QJsonArray>
#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <utils.h>
#include <QFontDatabase>
#include <mainscene.h>
#include <QGraphicsEffect>

using namespace std;
resultscene::resultscene(QWidget *parent)
    : basescene(parent)
{

}

resultscene::~resultscene()
{

}

void resultscene::close_to_mainscene(){

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
        if(pre == -2){
            mainscene* new_scene = new mainscene;
            new_scene->open_with_shutter();
        }else{
            songselect *new_scene = new songselect;
            new_scene->open_with_shutter(songlist,pre);
        }


        QTime dieTime = QTime::currentTime().addMSecs(5);
        while( QTime::currentTime() < dieTime ) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        //closecounter.stop();
        close();
    });
    closetimer.start();
    closeupdater.start();

}
void resultscene::initscene(){

    backbutton.load(BACK_BUTTON_PATH);
    scoresection.load(Scoresection_PATH);
    res_banner.load(Res_banner_PATH);
    pd_a.load(A_PATH);
    pd_aa.load(AA_PATH);
    pd_b.load(B_PATH);
    pd_c.load(C_PATH);
    pd_d.load(D_PATH);
    pd_ex.load(EX_PATH);
    pd_explus.load(EXPLUS_PATH);
    base.load(songs[songnumber].base);
    // 字体参照 https://www.bilibili.com/read/cv18904916
    drawtext(&label[4],QFont("Noto Sans CJK SC Regular", 15, false, false),70,33,"结果");

    scaling_pix(res_banner,1.3);
    setpix(&pixlabel[11],res_banner,960,550);
    scaling_pix(scoresection,1.25);
    setpix(&pixlabel[14],chara,1550,660);
    setpix(&pixlabel[12],scoresection,960,567);
    scaling_pix(base,0.95);
    setpix(&pixlabel[13],base,176+base.width()/2,663);

    setpix(&pixlabel[15],backbutton,161,1032);
    connect(&pixlabel[15],&QLabel_C::clicked,this,&resultscene::close_to_mainscene);

    int pdx = 950,pdy = 637;
    if(score >= 9900000){
        setpix(&pixlabel[16],pd_explus,pdx,pdy);
    }else if(score>=9800000){
        setpix(&pixlabel[16],pd_ex,pdx,pdy);
    }else if(score>=9500000){
        setpix(&pixlabel[16],pd_aa,pdx,pdy);
    }else if(score>=9200000){
        setpix(&pixlabel[16],pd_a,pdx,pdy);
    }else if(score>=8900000){
        setpix(&pixlabel[16],pd_b,pdx,pdy);
    }else if(score>=8600000){
        setpix(&pixlabel[16],pd_c,pdx,pdy);
    }else setpix(&pixlabel[16],pd_d,pdx,pdy);
    completebar.load(COMPLETE_BAR_PATH);
    setpix(&pixlabel[17],completebar,960,360);

    setcolor(&tex[4],QColor(121,121,121));
    drawtext_left(&tex[4],QFont("NanumBarunGothicOTF", 13, false, false),176,345,"MAX RECALL");
    setcolor(&tex[9],QColor(50,50,50));
    drawtext_left(&tex[9],QFont("NanumBarunGothicOTF", 15, false, false),356,345,to_string(maxrecall));

    drawtext_left(&tex[5],QFont("NanumBarunGothicOTF", 13, false, false),176,395,"Future "+to_string(songs[songnumber].difficulty));
    drawtext_with_shadow(&tex[6],&sha[6],QFont("NanumBarunGothicOTF", 30, false, false),960,200,songs[songnumber].name.toStdString());
    drawtext_with_shadow(&tex[7],&sha[7],QFont("NanumBarunGothicOTF", 14, false, false),960,270,songs[songnumber].writer.toStdString());
    //drawtext_left_with_shadow(&tex[8],&sha[8],QFont("Exo", 12, false, false),30,450,"BPM:"+to_string(songs[songnumber].bpm));
    string sc1 = to_string(score%1000);while(sc1.length()<3) sc1 = "0"+sc1;
    string sc2 = to_string((score%1000000)/1000);while(sc2.length()<3) sc2 = "0"+sc1;
    string sc = to_string(score/1000000);
    if(score != 10000000) sc = "0"+sc;
    sc = sc+"'"+sc2+"'"+sc1;
    drawtext_with_shadow(&tex[10],&sha[10],QFont("GeosansLight", 35, false, false),937,477,sc);
    setcolor(&tex[11],QColor(110,143,250));
    drawtext(&tex[11],QFont("NanumBarunGothicOTF", 13, false, false),900,760,"PURE");
    drawtext(&tex[14],QFont("GeosansLight", 20, false, false),990,755,to_string(pure));
    setcolor(&tex[12],QColor(150,150,150));
    drawtext(&tex[12],QFont("NanumBarunGothicOTF", 13, false, false),900,810,"FAR");
    drawtext(&tex[15],QFont("GeosansLight", 20, false, false),990,805,to_string(far));
    setcolor(&tex[13],QColor(150,150,150));
    drawtext(&tex[13],QFont("NanumBarunGothicOTF", 13, false, false),900,860,"LOST");
    drawtext(&tex[16],QFont("GeosansLight", 20, false, false),990,855,to_string(lost));
    drawtext(&tex[17],QFont("Noto Sans CJK SC Bold", 13, false, false),131,1020,"返回");
    connect(&tex[17],&QLabel_C::clicked,this,&resultscene::close_to_mainscene);
}
void resultscene::backtomain(){
    mainscene *ms = new mainscene;
    ms->open_with_shutter();
    QTime dieTime = QTime::currentTime().addMSecs(5);
    while( QTime::currentTime() < dieTime ) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    close();
//    dieTime = QTime::currentTime().addMSecs(100);
//    while( QTime::currentTime() < dieTime ) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
//    delete this;
}
void resultscene::openslot(int num,int sc,int mx,int pr,int fr,int lo,int PRE,vector<int> sl){
    songnumber = num;
    score = sc;
    maxrecall = mx;
    pure = pr;
    far = fr;
    lost = lo;
    pre = PRE;
    songlist = sl;
    initscene();
    open_with_shutter();
}
void resultscene::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.drawPixmap(960-background.width()/2,y_bg,background);
    //painter.drawPixmap(1550-chara.width()/2,660-chara.height()/2+y_cha,chara);
    //drawpix_inmiddle(painter,chara,1550,640);
    //painter.fillRect(0, 0, this->rect().width(), 100, QColor(255,255,255,255));
    painter.drawPixmap(0,0,topbar);
}
