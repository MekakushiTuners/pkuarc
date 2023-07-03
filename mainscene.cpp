#include "mainscene.h"
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
#include <QPalette>
#include <QColor>
#include <QGraphicsOpacityEffect>
#include "config.h"
#include "QLabel"
#include <QCoreApplication>
#include <QFontDatabase>

mainscene::mainscene(QWidget *parent) : basescene(parent)
{
    initscene();
}
void mainscene::initscene(){

    midsquare.load(MID_SQUARE_PATH);
    up_button.load(MAIN_UP_BUTTON_PATH);
    down_button.load(MAIN_DOWN_BUTTON_PATH);
    mid_button.load(MAIN_MID_BUTTON_PATH);
    midbut_shadow.load(MAIN_MID_SQUARE_SHADOW_PATH);
    text_world.load(TEXT_WORLD_PATH);
    // 字体参照 https://www.bilibili.com/read/cv18904916
    drawtext(&label[0],QFont("King's Gambit", 23, false, false),100,37,"EISAEA");
    setpix(&pixlabel[0],midsquare,760,540);
    setpix(&pixlabel[1],midbut_shadow,755,600);
    setpix(&pixlabel[2],text_world,750,540);
    for(int i=0;i<=2;i++){
        connect(&pixlabel[i],&QLabel_C::clicked,this,&mainscene::chapter_select_slot);
    }
    setpix(&pixlabel[3],mid_button,400,540);
    setpix(&pixlabel[4],up_button,505,370);
    setpix(&pixlabel[5],down_button,530,690);
    setcolor(&label[4],QColor(255,255,255));
    drawtext(&label[4],QFont("Noto Sans CJK SC Regular",20,false,false),330,520,"KRR推荐");
    connect(&label[4],&QLabel_C::clicked,this,&mainscene::close_to_songselect);
    connect(&pixlabel[3],&QLabel_C::clicked,this,&mainscene::close_to_songselect);
    setcolor(&label[5],QColor(255,255,255));
    drawtext(&label[5],QFont("Noto Sans CJK SC Regular",20,false,false),435,350,"随机开始");
    connect(&label[5],&QLabel_C::clicked,this,&mainscene::close_to_random_gamescene);
    connect(&pixlabel[4],&QLabel_C::clicked,this,&mainscene::close_to_random_gamescene);
    setcolor(&label[7],QColor(255,255,255));
    drawtext(&label[7],QFont("Noto Sans CJK SC Regular",20,false,false),440,670,"帮助");
    connect(&label[7],&QLabel_C::clicked,this,&mainscene::gethelp);
    connect(&pixlabel[5],&QLabel_C::clicked,this,&mainscene::gethelp);
    start();
//    lwing.load(LEFT_WING_PATH);
//    rwing.load(RIGHT_WING_PATH);
//    scaling_pix(lwing,0.6);
//    scaling_pix(rwing,0.6);
    //m_timer.setInterval(GAME_RATE);
}
void mainscene::start(){
    tottime.start();
    m_timer.start();

    connect(&m_timer,&QTimer::timeout,[=](){
        updateStatus(tottime.elapsed());
        update();
    });
}
void mainscene::updateStatus(int ntime){
    int moveh = background.height() - 1080;
    y_bg = ((int)(0.01*ntime))%(moveh*2);
    if(y_bg>=moveh) y_bg = moveh*2-y_bg;
    y_bg = -y_bg;
    y_cha = ((int)(0.005*ntime))%(80);
    if(y_cha>=40) y_cha = 80-y_cha;
    y_cha = -y_cha;
}
void mainscene::chapter_select_slot(){
//    songselect *select_page = new songselect;
//    select_page->openslot();
//    QTime dieTime = QTime::currentTime().addMSecs(5);
//    while( QTime::currentTime() < dieTime ) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
//    close();
    close_to_chap();
}
void mainscene::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);


    painter.drawPixmap(960-background.width()/2,y_bg,background);
    painter.drawPixmap(1550-chara.width()/2,660-chara.height()/2+y_cha,chara);
    //drawpix_inmiddle(painter,chara,1550,640);
    //painter.fillRect(0, 0, this->rect().width(), 100, QColor(255,255,255,255));
    painter.drawPixmap(0,0,topbar);
}
