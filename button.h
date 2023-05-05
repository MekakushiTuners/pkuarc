#ifndef BUTTON_H
#define BUTTON_H
#include<QPixmap>

class Button
{
public:
    Button(int m_time,int endtime);
    void setposition(int x,int y);
    QPixmap m_button;
    int m_X,m_Y;
    QRect m_rect;
    int m_time;
    int endtime;
    void fall(int ntime);
};

#endif // BUTTON_H
