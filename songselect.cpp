#include "songselect.h"
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
#include <chapterselect.h>

songselect::songselect(QWidget *parent) : QWidget(parent)
{
    //initscene();
    set_bg.load(Pausebg_PATH);
    scaling_pix(set_bg,1.55);
    icon_plus.load(ICON_PLUS_PATH);
    icon_minus.load(ICON_MINUS_PATH);
    ret_button.load(Pausebutton_PATH);
    first_seted = 0;
}
void songselect::initscene(){
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
    text_shadow.load(TEXT_SHADOW_PATH);
    scaling_pix(text_shadow,1.3);
    song_cell_corner_2.load(Song_cell_corner_2_PATH);
    song_cell_corner_light.load(Song_cell_corner_light_PATH);
    song_cell_name_underlay.load(Song_cell_name_underlay_PATH);
    song_cell_right.load(Song_cell_right_PATH);
    song_cell_selected_piece.load(Song_cell_selected_piece_PATH);
    text_start.load(TEXT_START_PATH);
    song_currentpack.load(Song_currentpack_PATH);
    new_badge.load(New_badge_PATH);
    jacket_glow.load(Jacket_glow_PATH);
    backbutton.load(BACK_BUTTON_PATH);
    difficulty_selector_0.load(Difficulty_selector_0_PATH);
    difficulty_selector_1.load(Difficulty_selector_1_PATH);
    difficulty_selector_2.load(Difficulty_selector_2_PATH);
    difficulty_selector_3_locked.load(Difficulty_selector_3_locked_PATH);
    song_score_tab.load(Song_score_tab_PATH);

    // 字体参照 https://www.bilibili.com/read/cv18904916
    drawtext(&label[0],QFont("Noto Sans CJK SC Regular", 15, false, false),110,33,"选择一首歌曲");
    setcolor(&label[1],QColor(8, 46, 84));
    drawtext(&label[1],QFont("GeosansLight", 20, false, false),760,33,"TateyamaAyano39");
    drawtext(&label[3],QFont("Noto Sans CJK SC Regular",12,false,false),1430,33,"残片");
//    for(int i=0;i<=19;i++) pixlabel[i] = new QLabel_C();
//    for(int i=0;i<=9;i++) label[i] = new QLabel_C(),slabel[i] = new QLabel_C(),songtext[i][0] = new QLabel_C(),songtext[i][1] = new QLabel_C(),shsongtext[i][0] = new QLabel_C(),shsongtext[i][1] = new QLabel_C();
    scaling_pix(song_currentpack,1.3);
    setpix(&pixlabel[5],song_currentpack,960,190);
    scaling_pix(new_badge,1.2);
    setpix(&pixlabel[6],new_badge,1115,135);
    setpix(&pixlabel[0],charabox,980,40);
    setpix(&pixlabel[1],ratingbox,1022,75);
    setpix(&pixlabel[2],setbox,1170,31);
    setpix(&pixlabel[3],seticon,1170,31);
    opacityEffect[0].setOpacity(0.3);
    pixlabel[3].setGraphicsEffect(&opacityEffect[0]);
    label[2].setStyleSheet("color:white;");
    drawtext(&label[2],QFont("Noto Sans CJK SC Bold",10,false,false),1170,31,"设定");
    connect(&label[2],&QLabel_C::clicked,this,&songselect::opensettings);
    connect(&pixlabel[2],&QLabel_C::clicked,this,&songselect::opensettings);
    connect(&pixlabel[3],&QLabel_C::clicked,this,&songselect::opensettings);
    setpix(&pixlabel[4],membox,1540,31);
    int stx = 1700,sty = 150;
    //for(int i=0;i<song_size;i++) songlist.push_back(i);
    sort(songlist.begin(),songlist.end(),[=](int a,int b){
        return songs[a].difficulty<songs[b].difficulty;
    });
    for(int i=0;i<songlist.size();i++){
        int nx = stx - i * 25;
        int ny = sty + i * 140;
        //printf("%d %d\n",i,songlist[i]);
        setsong(i,nx,ny);
        setpix(&songlabel[i][0],song_cell_corner_2,nx-200,ny);
        setpix(&songlabel[i][1],song_cell_corner_light,nx-211,ny+50);
        setpix(&songlabel[i][3],song_cell_right,nx+200,ny+13);
        setpix(&songlabel[i][2],song_cell_name_underlay,nx+81,ny+49);
        for(int j=0;j<=4;j++){
            //printf("%d %d\n",i,j);
            connect(&songlabel[i][j],&QLabel_C::clicked,[=](){
                nowindex = i;
                nowsong = songlist[i];
                //printf("%d %d %d\n",i,nowindex,nowsong);
                update();
            });
        }
        //setcolor(&songtext[i][0],QColor(255, 255, 255));
        drawtext_with_shadow(&songtext[i][0],&shsongtext[i][0],QFont("Exo", 23, false, false),nx-203,ny,to_string(songs[songlist[i]].difficulty));
        //setcolor(&songtext[i][1],QColor(255, 255, 255));
        drawtext_left_with_shadow(&songtext[i][1],&shsongtext[i][1],QFont("Exo", 14, false, false),nx-160,ny+49,songs[songlist[i]].name.toStdString());
   }
    nowindex = 0;
    nowsong = songlist[0];
    label[6].setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    slabel[6].setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //update();
    scaling_pix(jacket_glow,1.3);
    setpix(&pixlabel[7],jacket_glow,550,650);
    setpix(&pixlabel[8],backbutton,161,1032);

    drawtext(&label[4],QFont("Noto Sans CJK SC Bold", 13, false, false),131,1020,"返回");
    if(pre == -1){
        connect(&label[4],&QLabel_C::clicked,this,&songselect::close_to_mainscene);
        connect(&pixlabel[8],&QLabel_C::clicked,this,&songselect::close_to_mainscene);
    }else{
        connect(&label[4],&QLabel_C::clicked,this,&songselect::close_to_chap);
        connect(&pixlabel[8],&QLabel_C::clicked,this,&songselect::close_to_chap);
    }

    setpix(&pixlabel[9],song_score_tab,200,180);
    stx = 80;sty = 160;int dir = 160;
    setpix(&pixlabel[13],difficulty_selector_3_locked,stx+dir*3,sty);
    setpix(&pixlabel[12],difficulty_selector_2,stx+dir*2,sty);
    setpix(&pixlabel[11],difficulty_selector_1,stx+dir*1,sty);
    setpix(&pixlabel[10],difficulty_selector_0,stx,sty);
    scorelist_shadow.load(Scorelist_shadow_PATH);
    //connect(this,&songselect::playsignal,game,&gamescene::openslot);
    for(int i=15;i<=16;i++){
        connect(&pixlabel[i],&QLabel_C::clicked,this,&songselect::close_to_gamescene);
    } // TEXT_START
    stx = 1700,sty = 150;
    int nowx = stx -nowindex*25;
    int nowy = sty +nowindex*140;
    setpix(&pixlabel[14],song_cell_selected_piece,nowx-251,nowy+13);
    setpix(&pixlabel[16],text_shadow,nowx-60,nowy);
    setpix(&pixlabel[15],text_start,nowx-60,nowy);
    QPixmap mp;mp.load(songs[nowsong].base);scaling_pix(mp,1.14);
    setpix(&pixlabel[17],mp,546,645);
    opacityEffect[1].setOpacity(0.3);
    pixlabel[18].setGraphicsEffect(&opacityEffect[1]);
    setpix(&pixlabel[18],scorelist_shadow,220,350);

    drawtext_left_with_shadow(&label[6],&slabel[6],QFont("Exo", 30, false, false),30,350,songs[nowsong].name.toStdString());
    drawtext_left_with_shadow(&label[7],&slabel[7],QFont("Exo", 15, false, false),30,410,songs[nowsong].writer.toStdString());
    drawtext_left_with_shadow(&label[8],&slabel[8],QFont("Exo", 12, false, false),30,450,"BPM:"+to_string(songs[nowsong].bpm));

    //setcolor(&label[5],QColor(255, 255, 255));
    drawtext_with_shadow(&label[5],&slabel[5],QFont("Exo", 20, false, false),391,147,to_string(songs[nowsong].difficulty));

    if(pre == -1){
        setcolor(&label[9],QColor(255, 255, 255));
        drawtext(&label[9],QFont("Exo",14,false,false),960,180,"Ayano's favorite");
        setcolor(&label[10],QColor(255, 255, 255));
        drawtext(&label[10],QFont("Exo",14,false,false),960,140,to_string(39));
        setcolor(&label[11],QColor(200, 200, 200));
        drawtext(&label[11],QFont("Exo",11,false,false),890,140,"PACKS");
    }else{
        setcolor(&label[9],QColor(255, 255, 255));
        drawtext(&label[9],QFont("Exo",14,false,false),960,180,pack_name[pre]);
        setcolor(&label[10],QColor(255, 255, 255));
        drawtext(&label[10],QFont("Exo",14,false,false),960,140,to_string(pre)+"/"+to_string(8));
        setcolor(&label[11],QColor(200, 200, 200));
        drawtext(&label[11],QFont("Exo",11,false,false),890,140,"PACKS");
    }
    drawtext_with_shadow(&label[12],&slabel[12],QFont("GeosansLight", 13, false, false),1022,75,"11.45");
    m_timer.setInterval(GAME_RATE);
    //start();
}
void songselect::close_to_chap(){
    closetimer.setInterval(500);
    closeupdater.setInterval(1);
    //closecounter.start();
    connect(&closeupdater,&QTimer::timeout,[=](){
        int rest = closetimer.remainingTime();
        if(rest>=100){
            double x_r = 1.0*(rest-100)/400;
            int nxl = shutter_l.width()/2-(x_r*x_r)*shutter_l.width();
            int nxr = 1920-shutter_r.width()/2+(x_r*x_r)*shutter_r.width();
            setpix(&shut[2],shutter_l,nxl,540);
            setpix(&shut[3],shutter_r,nxr,540);
        }


    });
    connect(&closetimer,&QTimer::timeout,[&](){
        closetimer.stop();
        closeupdater.stop();
        chapterselect* new_scene = new chapterselect;
        new_scene->open_with_shutter(pre);
        QTime dieTime = QTime::currentTime().addMSecs(5);
        while( QTime::currentTime() < dieTime ) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        //closecounter.stop();
        close();
    });
    closetimer.start();
    closeupdater.start();

}
void songselect::close_to_mainscene(){

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
void songselect::start(){
    tottime.start();
    m_timer.start();

    connect(&m_timer,&QTimer::timeout,[=](){
        //updateStatus(tottime.elapsed());
        update();
    });
}
void songselect::backtomain(){
    mainscene *ms = new mainscene;
    ms->open_with_shutter();
    QTime dieTime = QTime::currentTime().addMSecs(5);
    while( QTime::currentTime() < dieTime ) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    close();
//    dieTime = QTime::currentTime().addMSecs(100);
//    while( QTime::currentTime() < dieTime ) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
//    ;
}
void songselect::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.drawPixmap(960-background.width()/2,0,background);
    painter.drawPixmap(0,0,topbar);
    int stx = 1700,sty = 150;
    int nowx = stx -nowindex*25;
    int nowy = sty +nowindex*140;
    if(!opentimer.isActive()){


        setpix(&pixlabel[14],song_cell_selected_piece,nowx-251,nowy+13);
        setpix(&pixlabel[16],text_shadow,nowx-60,nowy);
        setpix(&pixlabel[15],text_start,nowx-60,nowy);
        QPixmap mp;mp.load(songs[nowsong].base);scaling_pix(mp,1.14);
        setpix(&pixlabel[17],mp,546,645);
        opacityEffect[1].setOpacity(0.3);
        pixlabel[18].setGraphicsEffect(&opacityEffect[1]);
        setpix(&pixlabel[18],scorelist_shadow,220,350);

        drawtext_left_with_shadow(&label[6],&slabel[6],QFont("Exo", 30, false, false),30,350,songs[nowsong].name.toStdString());
        drawtext_left_with_shadow(&label[7],&slabel[7],QFont("Exo", 15, false, false),30,410,songs[nowsong].writer.toStdString());
        drawtext_left_with_shadow(&label[8],&slabel[8],QFont("Exo", 12, false, false),30,450,"BPM:"+to_string(songs[nowsong].bpm));

        //setcolor(&label[5],QColor(255, 255, 255));
        drawtext_with_shadow(&label[5],&slabel[5],QFont("Exo", 20, false, false),391,147,to_string(songs[nowsong].difficulty));

    }
}
