#ifndef BUTTON_H
#define BUTTON_H
#include<QPixmap>
#include<vector>
#include<utils.h>
using namespace std;

class Button
{
public:
    Button(int m_time,int endtime,vector<int> pdtime);
    void setposition(double x,double y);
    QPixmap m_button;
    double m_X,m_Y;
    QRect m_rect;
    int m_time;
    int endtime;
    // 如果endtime = m_time 则为单个button
    void fall(int ntime);
    vector<int> pdtime; // 长条的判定时间点
    int pdpos; // 上面vector的pos指针
    int pressed;
    int first_pressed;
};

#endif // BUTTON_H
