#include "mainscene.h"
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

mainscene::mainscene(QWidget *parent)
    : QMainWindow(parent)
{
    initscene();
}

mainscene::~mainscene()
{

}

void mainscene::initscene(){
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    setWindowTitle(GAME_TITLE);
    setWindowIcon(QIcon(GAME_ICON));
    m_timer.setInterval(GAME_RATE);
    setFocusPolicy(Qt::StrongFocus);
    checktype = 0;
    checkimage[1].load(ICON_PERFECT_PATH);
    checkimage[2].load(ICON_GREAT_PATH);
    checkimage[3].load(ICON_GOOD_PATH);
    checkimage[4].load(ICON_MISS_PATH);
    combo = 0;
}
void mainscene::playGame(){
    //static int ntime = 0; // ms
    m_timer.start();
    tottime.start();
    m_track[0].setposition(660,0);
    m_track[1].setposition(860,0);
    m_track[2].setposition(1060,0);
    m_track[3].setposition(1260,0);
    for(int i=0;i<4;i++)
        for(int j=1;j<=200;j++)
            m_track[i].push_button(Button(WAIT_TIME + j*200,WAIT_TIME + j*200));

    for(int i=0;i<4;i++)
        connect(&m_track[i],&Track::checksignal,this,&mainscene::checkslot);

    connect(&m_timer,&QTimer::timeout,[=](){
        //ntime += GAME_RATE;
        updateStatus(tottime.elapsed());
        update();
    });
}
void mainscene::checkslot(int m_type){
    checktype = m_type;
    if(m_type <=2) combo++;
    else combo = 0;
}
void mainscene::updateStatus(int ntime){
    for(int i=0;i<4;i++)
        m_track[i].uptateStatus(ntime);
}
void mainscene::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QFont font("汉仪粗仿宋简", 60, QFont::Bold, false);   //字体，大小，粗体，斜体
    painter.setFont(font);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QColor(57, 175, 213));

    painter.drawLine(QPointF(0, CHECKLINE_POS), QPointF(GAME_WIDTH, CHECKLINE_POS)); // draw checkline

    painter.setPen(QColor(0, 0, 0));
    QFontMetrics fm = painter.fontMetrics();
   QString a = QString::number(combo);
    int width = fm.width(a);
    int height = fm.ascent()+fm.descent();
    //printf("%d %d\n",width,height);
    QRectF rect(1560-width/2,750-height/2,width,height);
    painter.drawText(rect,a);

    for(int i=0;i<4;i++)
        m_track[i].drawtrack(painter);
    if(checktype){
        painter.drawPixmap(1460,540,checkimage[checktype]);

    }

}
void mainscene::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key_A:
            m_track[0].onpressed(tottime.elapsed());
            break;
        case Qt::Key_S:
            m_track[1].onpressed(tottime.elapsed());
            break;
        case Qt::Key_K:
            m_track[2].onpressed(tottime.elapsed());
            break;
        case Qt::Key_L:
            m_track[3].onpressed(tottime.elapsed());
            break;
    }
}
