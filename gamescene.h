#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QMainWindow>
#include <qtimer.h>
#include <button.h>
#include <track.h>
#include <QTime>
#include <QLabel>


class gamescene : public QWidget
{
    Q_OBJECT

public:
    gamescene(QWidget *parent = 0);
    ~gamescene();
    void initscene();
    int songnumber;
    QTimer m_timer;
    QTime tottime;
    void playGame();
    void paintEvent(QPaintEvent *event);
    void updateStatus(int ntime);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    Track m_track[4];
    int checktype;
    int combo;
    int nowsong;
    QPixmap checkimage[5];
    QLabel label[2];
    QPixmap background;
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
public slots:
    void checkslot(int m_type);
    void openslot(int sn);
};

#endif // GAMESCENE_H
