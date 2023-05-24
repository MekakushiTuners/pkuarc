#ifndef UTILS_H
#define UTILS_H
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <iostream>
#include <QString>
using namespace std;

class QLabel_C: public QLabel{
    Q_OBJECT
public:
    QLabel_C(QWidget* parent = nullptr) : QLabel(parent) {}
    virtual void mousePressEvent(QMouseEvent* event) override{
        if (event->button() == Qt::LeftButton){
            emit clicked();
            //printf("Label clicked!\n");
        }
        QLabel::mousePressEvent(event);
    }
signals:
    void clicked();
};

class Song{
public:
    int difficulty;
    QString base;
    QString path,mcpath;
    QString name,writer;
    int bpm;
    Song(int d,QString b,QString nm,QString pa,QString mcpa,QString wr,int bpm):difficulty(d),base(b),name(nm),path(pa),mcpath(mcpa),writer(wr),bpm(bpm){

    }
};
extern Song songs[5];

#endif // UTILS_H
