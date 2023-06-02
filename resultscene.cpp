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
    : QWidget(parent)
{
    shutter_l.load(SHUTTER_L_PATH);
    shutter_r.load(SHUTTER_R_PATH);
    scaling_pix(shutter_l,1.52);
    scaling_pix(shutter_r,1.52);

    set_bg.load(Pausebg_PATH);
    scaling_pix(set_bg,1.55);
    icon_plus.load(ICON_PLUS_PATH);
    icon_minus.load(ICON_MINUS_PATH);
    ret_button.load(Pausebutton_PATH);
    first_seted = 0;
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
    setAttribute(Qt::WA_DeleteOnClose);
    y_bg = y_cha = 0;
    for(int i=0;i<font_size;i++) QFontDatabase::addApplicationFont(font_path[i]);
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    setWindowTitle(GAME_TITLE);
    setWindowIcon(QIcon(GAME_ICON));
    m_timer.setInterval(GAME_RATE);
    setFocusPolicy(Qt::StrongFocus);
    background.load(MAIN_BACKGROUND_PATH);
    scaling_pix(background,1.6);
    //background = background.scaled(1.6*background.width(),1.6*background.height(),Qt::KeepAspectRatio);
    ratingbox.load(RATING_PATH);
    scaling_pix(ratingbox,0.55);
    midsquare.load(MID_SQUARE_PATH);
    charabox.load(CHARA_ICON_PATH);
    scaling_pix(charabox,0.7);
    chara.load(CHARA_PATH);
    topbar.load(TOP_BAR_PATH);
    scaling_pix(topbar,1.25);
    setbox.load(SETTING_BOX_PATH);
    scaling_pix(setbox,1.25);
    seticon.load(SETTING_ICON_PATH);
    membox.load(MEMORY_BOX_PATH);
    scaling_pix(membox,1.25);
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
    setcolor(&label[1],QColor(8, 46, 84));
    drawtext(&label[1],QFont("GeosansLight", 20, false, false),760,33,"TateyamaAyano39");
    drawtext(&label[3],QFont("Noto Sans CJK SC Regular",12,false,false),1430,33,"残片");
    drawtext(&label[4],QFont("Noto Sans CJK SC Regular", 15, false, false),70,33,"结果");
    setpix(&pixlabel[6],charabox,980,40);
    setpix(&pixlabel[7],ratingbox,1022,75);
    setpix(&pixlabel[8],setbox,1170,31);
    setpix(&pixlabel[9],seticon,1170,31);

    opacityEffect[0] = new QGraphicsOpacityEffect;
    opacityEffect[0]->setOpacity(0.3);
    pixlabel[9].setGraphicsEffect(opacityEffect[0]);

    label[2].setStyleSheet("color:white;");
    drawtext(&label[2],QFont("Noto Sans CJK SC Bold",10,false,false),1170,31,"设定");
    connect(&label[2],&QLabel_C::clicked,this,&resultscene::opensettings);
    connect(&pixlabel[8],&QLabel_C::clicked,this,&resultscene::opensettings);
    connect(&pixlabel[9],&QLabel_C::clicked,this,&resultscene::opensettings);
    setpix(&pixlabel[10],membox,1540,31);
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
    drawtext_with_shadow(&tex[18],&sha[18],QFont("GeosansLight", 13, false, false),1022,75,"11.45");
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
