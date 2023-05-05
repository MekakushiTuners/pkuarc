#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include <qtimer.h>
#include <button.h>
#include <track.h>
#include <QTime>



class mainscene : public QMainWindow
{
    Q_OBJECT

public:
    mainscene(QWidget *parent = 0);
    ~mainscene();
    void initscene();
    QTimer m_timer;
    QTime tottime;
    void playGame();
    void paintEvent(QPaintEvent *event);
    void updateStatus(int ntime);
    void keyPressEvent(QKeyEvent *event);
    Track m_track[4];
    int checktype;
    int combo;
    QPixmap checkimage[5];
public slots:
    void checkslot(int m_type);
};

#endif // MAINSCENE_H
