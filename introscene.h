#ifndef introscene_H
#define introscene_H

#include <QWidget>
#include <config.h>
#include <QTime>
#include <qtimer.h>
#include <mainscene.h>
#include <QMouseEvent>

class introscene : public QWidget
{
    Q_OBJECT

public:
    introscene(QWidget *parent = nullptr);
    ~introscene();
    void initscene();
    void startgame();
    QTime tottime;
    QTimer m_timer;
    int op_finished;
    int bg_y;
    int lp; // 0 - 255
    double tp; // 0 - 1
    QPixmap background;
    QPixmap game_title_icon;
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void updateStatus(int ntime);
    mainscene* new_game;

signals:
    void gamesignal();
};

#endif // introscene_H
