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

mainscene::mainscene(QWidget *parent) : QWidget(parent)
{
    initscene();
}
void mainscene::initscene(){
    setAttribute(Qt::WA_DeleteOnClose);
    shutter_l.load(SHUTTER_L_PATH);
    shutter_r.load(SHUTTER_R_PATH);
    scaling_pix(shutter_l,1.52);
    scaling_pix(shutter_r,1.52);
    for(int i=0;i<font_size;i++) QFontDatabase::addApplicationFont(font_path[i]);
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    setWindowTitle(GAME_TITLE);
    setWindowIcon(QIcon(GAME_ICON));
    setFocusPolicy(Qt::StrongFocus);
    background.load(MAIN_BACKGROUND_PATH);
    scaling_pix(background,1.6);
    //background = background.scaled(1.6*background.width(),1.6*background.height(),Qt::KeepAspectRatio);
    ratingbox.load(RATING_PATH);
    scaling_pix(ratingbox,0.55);
    midsquare.load(MID_SQUARE_PATH);
    up_button.load(MAIN_UP_BUTTON_PATH);
    down_button.load(MAIN_DOWN_BUTTON_PATH);
    mid_button.load(MAIN_MID_BUTTON_PATH);
    charabox.load(CHARA_ICON_PATH);
    scaling_pix(charabox,0.7);
    chara.load(CHARA_PATH);
    midbut_shadow.load(MAIN_MID_SQUARE_SHADOW_PATH);
    text_world.load(TEXT_WORLD_PATH);
    topbar.load(TOP_BAR_PATH);
    scaling_pix(topbar,1.25);
    setbox.load(SETTING_BOX_PATH);
    scaling_pix(setbox,1.25);
    seticon.load(SETTING_ICON_PATH);
    membox.load(MEMORY_BOX_PATH);
    scaling_pix(membox,1.25);
    // 字体参照 https://www.bilibili.com/read/cv18904916
    drawtext(label[0],QFont("King's Gambit", 23, false, false),100,37,"EISAEA");
    //label[1].setStyleSheet("color:purple;");
    setcolor(&label[1],QColor(8, 46, 84));
    drawtext(label[1],QFont("GeosansLight", 20, false, false),760,33,"TateyamaAyano39");
    drawtext(label[3],QFont("Noto Sans CJK SC Regular",12,false,false),1430,33,"残片");
    //select_page = new songselect();
    //connect(this,&gamescene::gamesignal,new_game,&mainscene::openslot);
    for(int i=0;i<=10;i++) pixlabel[i] = new QLabel_C();
    setpix(pixlabel[0],midsquare,760,540);
    setpix(pixlabel[1],midbut_shadow,755,600);
    setpix(pixlabel[2],text_world,750,540);
    for(int i=0;i<=2;i++){
        connect(pixlabel[i],&QLabel_C::clicked,this,&mainscene::song_select_slot);
    }
    setpix(pixlabel[3],mid_button,400,540);
    setpix(pixlabel[4],up_button,505,370);
    setpix(pixlabel[5],down_button,530,690);
    setpix(pixlabel[6],charabox,980,40);
    setpix(pixlabel[7],ratingbox,1022,75);
    setpix(pixlabel[8],setbox,1170,31);
    setpix(pixlabel[9],seticon,1170,31);
    opacityEffect[0].setOpacity(0.3);
    pixlabel[9]->setGraphicsEffect(&opacityEffect[0]);
    label[2].setStyleSheet("color:white;");
    drawtext(label[2],QFont("Noto Sans CJK SC Bold",10,false,false),1170,31,"设定");
    setpix(pixlabel[10],membox,1540,31);

    //setpix(pixlabel[10],down_button,530,690);
//    drawpix_inmiddle(painter,charabox,980,40);
//    drawpix_inmiddle(painter,ratingbox,1022,75);
//    drawpix_inmiddle(painter,setbox,1170,31);
//    painter.setOpacity(0.3);
//    drawpix_inmiddle(painter,seticon,1170,31);
//    painter.setOpacity(1);
//    drawpix_inmiddle(painter,membox,1540,31);
    m_timer.setInterval(GAME_RATE);
    y_bg = 0;
    y_cha = 0;
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
void mainscene::song_select_slot(){
//    songselect *select_page = new songselect;
//    select_page->openslot();
//    QTime dieTime = QTime::currentTime().addMSecs(5);
//    while( QTime::currentTime() < dieTime ) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
//    close();
    close_with_shutter<songselect>();
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
