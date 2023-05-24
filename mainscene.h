#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <songselect.h>
#include <QWidget>
#include <config.h>
#include <QTime>
#include <qtimer.h>
#include <qpainter.h>
#include "qpixmap.h"
#include "iostream"
#include "QLabel"
#include "QFontMetrics"
#include "qtimer.h"
#include "QGraphicsOpacityEffect"
#include "QMouseEvent"
#include "utils.h"


using namespace std;

//class QLabel_C: public QLabel{
//    Q_OBJECT
//public:
//    QLabel_C(QWidget* parent = nullptr) : QLabel(parent) {}
//    virtual void mousePressEvent(QMouseEvent* event) override{
//        if (event->button() == Qt::LeftButton){
//            emit clicked();
//            //printf("Label clicked!\n");
//        }
//        QLabel::mousePressEvent(event);
//    }
//signals:
//    void clicked();
//};
class mainscene : public QWidget
{
    Q_OBJECT
public:
    mainscene(QWidget *parent = nullptr);
    void initscene();
    void paintEvent(QPaintEvent *event);
    void updateStatus(int ntime);
    songselect *select_page;
    QPixmap background,ratingbox,midsquare,charabox,up_button,mid_button,down_button;
    QPixmap chara,text_world,midbut_shadow,topbar,setbox,seticon,membox;
    QLabel label[10];
    QLabel_C* pixlabel[20];
    QTime tottime;
    QTimer m_timer;
    QGraphicsOpacityEffect opacityEffect[1];
    int y_bg;
    int y_cha;
    void start();
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
    void drawtext(QLabel &label,QFont font,int x,int y,string s){
        label.setParent(this);
        label.setText(QString::fromStdString(s));
        label.setFont(font);
        label.setAlignment(Qt::AlignCenter);
        QFontMetrics fm(font);
        QString a = QString::fromStdString(s);
        int width = fm.width(a);
        int height = fm.ascent()+fm.descent();
        label.move(x-width/2,y-height/2);
        label.show();
    }
signals:

public slots:
    void openslot();
    void song_select_slot();
};

#endif // MAINSCENE_H
