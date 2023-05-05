#ifndef TRACK_H
#define TRACK_H
#include<vector>
#include<button.h>

using namespace std;

class Track:public QObject
{
    Q_OBJECT

public:
    Track(QObject *parent = 0);
    ~Track();
    int m_X,m_Y;
    vector<Button> ontrack_but;
    vector<Button> nex_but;
    int pos1,pos2;
    void push_button(Button a);
    void uptateStatus(int ntime);
    void drawtrack(QPainter &painter);
    void setposition(int x,int y);
    void onpressed(int ntime);
signals:
    void checksignal(int m_type);
};

#endif // TRACK_H
