#include "basescene.h"
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
basescene::basescene(QWidget *parent)
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

    setcolor(&lb[1],QColor(8, 46, 84));
    drawtext(&lb[1],QFont("GeosansLight", 20, false, false),760,33,"TateyamaAyano39");
    drawtext(&lb[3],QFont("Noto Sans CJK SC Regular",12,false,false),1430,33,"残片");
    setpix(&pb[6],charabox,980,40);
    setpix(&pb[7],ratingbox,1022,75);
    setpix(&pb[8],setbox,1170,31);
    setpix(&pb[9],seticon,1170,31);

    opacityEffect[0] = new QGraphicsOpacityEffect;
    opacityEffect[0]->setOpacity(0.3);
    pb[9].setGraphicsEffect(opacityEffect[0]);

    lb[2].setStyleSheet("color:white;");
    drawtext(&lb[2],QFont("Noto Sans CJK SC Bold",10,false,false),1170,31,"设定");
    connect(&lb[2],&QLabel_C::clicked,this,&basescene::opensettings);
    connect(&pb[8],&QLabel_C::clicked,this,&basescene::opensettings);
    connect(&pb[9],&QLabel_C::clicked,this,&basescene::opensettings);
    setpix(&pb[10],membox,1540,31);

    drawtext_with_shadow(&tex[18],&sha[18],QFont("GeosansLight", 13, false, false),1022,75,"11.45");
    drawtext_with_shadow(&tex[19],&sha[19],QFont("GeosansLight", 14, false, false),1540,33,"0");
}
