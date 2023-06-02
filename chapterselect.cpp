#include "chapterselect.h"
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
#include "QCoreApplication"
#include "mainscene.h"
#include "QFontDatabase"

chapterselect::chapterselect(QWidget *parent) : QWidget(parent)
{
    set_bg.load(Pausebg_PATH);
    scaling_pix(set_bg,1.55);
    icon_plus.load(ICON_PLUS_PATH);
    icon_minus.load(ICON_MINUS_PATH);
    ret_button.load(Pausebutton_PATH);
    first_seted = 0;

}
void chapterselect::initscene(){
    setAttribute(Qt::WA_DeleteOnClose);
    for(int i=0;i<font_size;i++) QFontDatabase::addApplicationFont(font_path[i]);
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    setWindowTitle(GAME_TITLE);
    setWindowIcon(QIcon(GAME_ICON));
    setFocusPolicy(Qt::StrongFocus);
    shutter_l.load(SHUTTER_L_PATH);
    shutter_r.load(SHUTTER_R_PATH);
    scaling_pix(shutter_l,1.52);
    scaling_pix(shutter_r,1.52);
    background.load(SONGSELECT_BACKGROUND_PATH);
    scaling_pix(background,1.6);
    //background = background.scaled(1.6*background.width(),1.6*background.height(),Qt::KeepAspectRatio);
    ratingbox.load(RATING_PATH);
    scaling_pix(ratingbox,0.55);
    charabox.load(CHARA_ICON_PATH);
    scaling_pix(charabox,0.7);
    topbar.load(TOP_BAR_PATH);
    scaling_pix(topbar,1.25);
    setbox.load(SETTING_BOX_PATH);
    scaling_pix(setbox,1.25);
    seticon.load(SETTING_ICON_PATH);
    membox.load(MEMORY_BOX_PATH);
    scaling_pix(membox,1.25);
    backbutton.load(BACK_BUTTON_PATH);
    arrow_l.load(ARROW_PATH);
    arrow_r.load(ARROW_R_PATH);
    title_back.load(TITLE_BACK_PATH);
    QString prefix = ":/res/world/";
   // exit(0);
    for(int i=1;i<=7;i++){
        //printf("%s\n",(prefix + ('0'+i) + "_b.jpg").toStdString().c_str());
        bg[i].load(prefix + ('0'+i) + "_b.jpg");
        scaling_pix(bg[i],1.5);
        title[i].load(prefix + ('0'+i) + "_t.png");
        square[i].load(prefix + ('0'+i) + "_d.png");
    }
    bg[8].load(prefix + ("1001") + "_b.jpg");
    scaling_pix(bg[8],1.5);
    title[8].load(prefix + ("1001") + "_t.png");
    square[8].load(prefix + ("1001") + "_d.png");
    songlist[1] = {0,2,5,33,20,41};
    //printf("%d %d %d %d\n",songlist[1].size(),songlist[1][0],songlist[1][1],songlist[1][2]);
    songlist[2] = {37,1,6,11,16};
    songlist[3] = {7,12,22,21,39};
    songlist[4] = {3,32,13,15,18};
    songlist[5] = {4,9,14,19,24};
    songlist[6] = {26,35,34,40,23};
    songlist[7] = {30,31,28,29,37};
    songlist[8] = {27,8,10,25,38,17};
    for(int i=1;i<=7;i++){
        scaling_pix(title[i],0.9);
        scaling_pix(square[i],0.9);
    }
    scaling_pix(arrow_l,0.9);
    scaling_pix(arrow_r,0.9);
    // 字体参照 https://www.bilibili.com/read/cv18904916
    drawtext(&label[0],QFont("Noto Sans CJK SC Regular", 15, false, false),110,33,"World");
    setcolor(&label[1],QColor(8, 46, 84));
    drawtext(&label[1],QFont("GeosansLight", 20, false, false),760,33,"TateyamaAyano39");
    drawtext(&label[3],QFont("Noto Sans CJK SC Regular",12,false,false),1430,33,"残片");
    setpix(&pixlabel[8],backbutton,161,1032);
    connect(&pixlabel[8],&QLabel_C::clicked,this,&chapterselect::close_to_mainscene);
    drawtext(&label[4],QFont("Noto Sans CJK SC Bold", 13, false, false),131,1020,"主菜单");
    connect(&label[4],&QLabel_C::clicked,this,&chapterselect::close_to_mainscene);
//    for(int i=0;i<=19;i++) pixlabel[i] = new QLabel_C();
//    for(int i=0;i<=9;i++) label[i] = new QLabel_C(),slabel[i] = new QLabel_C(),songtext[i][0] = new QLabel_C(),songtext[i][1] = new QLabel_C(),shsongtext[i][0] = new QLabel_C(),shsongtext[i][1] = new QLabel_C();
    setpix(&pixlabel[0],charabox,980,40);
    setpix(&pixlabel[1],ratingbox,1022,75);
    setpix(&pixlabel[2],setbox,1170,31);
    setpix(&pixlabel[3],seticon,1170,31);
    opacityEffect[0].setOpacity(0.3);
    pixlabel[3].setGraphicsEffect(&opacityEffect[0]);
    label[2].setStyleSheet("color:white;");
    drawtext(&label[2],QFont("Noto Sans CJK SC Bold",10,false,false),1170,31,"设定");
    connect(&label[2],&QLabel_C::clicked,this,&chapterselect::opensettings);
    connect(&pixlabel[2],&QLabel_C::clicked,this,&chapterselect::opensettings);
    connect(&pixlabel[3],&QLabel_C::clicked,this,&chapterselect::opensettings);
    setpix(&pixlabel[4],membox,1540,31);
    m_timer.setInterval(GAME_RATE);
    //nowchap = 1;
    //setpix(&label[5],bg[nowchap],960,540);
    setpix(&label[6],square[nowchap],960,610);
    title_back = title_back.scaled(2*title_back.width(),title_back.height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    opacityEffect[1].setOpacity(0.7);
    label[10].setGraphicsEffect(&opacityEffect[1]);
    setpix(&label[10],title_back,960,300);
    setpix(&label[7],title[nowchap],960,270);
    setpix(&label[8],arrow_l,560,610);
    connect(&label[8],&QLabel_C::clicked,this,&chapterselect::go_left);
    setpix(&label[9],arrow_r,1360,610);
    connect(&label[9],&QLabel_C::clicked,this,&chapterselect::go_right);
    connect(&label[6],&QLabel_C::clicked,[&](){
        close_to_songselect();
    });
    drawtext_with_shadow(&label[11],&slabel[11],QFont("GeosansLight", 13, false, false),1022,75,"11.45");
}
void chapterselect::close_to_mainscene(){

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
        mainscene* new_scene = new mainscene;
        new_scene->open_with_shutter();
        QTime dieTime = QTime::currentTime().addMSecs(5);
        while( QTime::currentTime() < dieTime ) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        //closecounter.stop();
        close();
    });
    closetimer.start();
    closeupdater.start();
}
void chapterselect::start(){
    tottime.start();
    m_timer.start();
    connect(&m_timer,&QTimer::timeout,[=](){
        //updateStatus(tottime.elapsed());
        update();
    });
}
void chapterselect::backtomain(){
    mainscene *ms = new mainscene;
    ms->open_with_shutter();
    QTime dieTime = QTime::currentTime().addMSecs(5);
    while( QTime::currentTime() < dieTime ) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    close();
//    dieTime = QTime::currentTime().addMSecs(100);
//    while( QTime::currentTime() < dieTime ) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
//    ;
}
void chapterselect::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.drawPixmap(960-bg[nowchap].width()/2,0,bg[nowchap]);
    painter.drawPixmap(0,0,topbar);
    setpix(&label[6],square[nowchap],960,610);
    setpix(&label[10],title_back,960,300);
    setpix(&label[7],title[nowchap],960,270);
    //int stx = 1700,sty = 150;
    //int nowx = stx -nowsong*25;
    //int nowy = sty +nowsong*140;
    if(!opentimer.isActive()){

    }
}
