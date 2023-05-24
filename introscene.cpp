#include "introscene.h"
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
#include <QPalette>
#include <QColor>
#include <QCoreApplication>
#include <QMouseEvent>



introscene::introscene(QWidget *parent) :
    QWidget(parent)
{
    initscene();
}

void introscene::initscene(){
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    setWindowTitle(GAME_TITLE);
    setWindowIcon(QIcon(GAME_ICON));
    setFocusPolicy(Qt::StrongFocus);
    m_timer.setInterval(GAME_RATE);
    bg_y = 0;
    op_finished = 0;
    lp = 0;
    tp = 0;
    background.load(BACKGROUND_PATH);
    game_title_icon.load(ARC_ICON_PATH);
    //new_game.show();
    new_game = new mainscene();
    connect(this,&introscene::gamesignal,new_game,&mainscene::openslot);
    startgame();
//    QPalette pal(palette());
//    pal.setColor(QPalette::Background, QColor(0,0,0,100));
//    setAutoFillBackground(true);
//    setPalette(pal);
}
void introscene::startgame(){
    tottime.start();
    m_timer.start();

    connect(&m_timer,&QTimer::timeout,[=](){
        updateStatus(tottime.elapsed());
        update();
    });
}
void introscene::updateStatus(int ntime){
    int leadtime = 2000;
    int rolltime = 3000;
    int titletime = 3500;
    if(ntime <= leadtime) lp = 255 - (1.0 * ntime / leadtime * 255);
    else{
        lp = 0;
    }
    if(ntime <= rolltime) bg_y = (ntime - rolltime)/ 10;
    else if(ntime <= titletime){
        tp = (1.0 * (ntime - rolltime) / (titletime - rolltime) );
    }else tp = 1;
}
void introscene::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    //painter.setPen();
    //QRectF rec(-1, -1, 1921, 1081);
    int ntime = tottime.elapsed();
    painter.drawPixmap(-760,bg_y,background);
    painter.fillRect(0, 0, this->rect().width(),this->rect().height(), QColor(0,0,0,lp));
    if(ntime > 3000){
        painter.setOpacity(tp);
        painter.drawPixmap(960 - game_title_icon.width()/2,530-60*tp, game_title_icon);
    }
    //painter.fillRect(0, 0, this->rect().width(), this->rect().height(), QColor(0,0,0,lp));
    //painter.fillRect(0, 0, this->rect().width(), this->rect().height(), QColor(0,0,0,lp));
}
void introscene::keyPressEvent(QKeyEvent *event){
    emit gamesignal();
    //printf("%d\n",1);
    QTime dieTime = QTime::currentTime().addMSecs(5);
    while( QTime::currentTime() < dieTime ) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    close();
}
void introscene::mousePressEvent(QMouseEvent *event){
    emit gamesignal();
    //printf("%d\n",1);
    QTime dieTime = QTime::currentTime().addMSecs(5);
    while( QTime::currentTime() < dieTime ) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    close();
}
introscene::~introscene()
{

}
