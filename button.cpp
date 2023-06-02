#include "button.h"
#include "config.h"

Button::Button(int m_time,int endtime,vector<int> pdtime):m_time(m_time),endtime(endtime),pdtime(pdtime)
{
    if(m_time == endtime){
        m_button.load(BUTTON_PATH);   
    }
    else m_button.load(LONGBUT_PATH);
    m_button = m_button.scaled(m_button.width()*0.7,m_button.height()*0.7,Qt::KeepAspectRatio);
    m_X = GAME_WIDTH*0.5 - m_button.width()*0.5;
    m_Y = 0 - m_button.height()*0.5;
    m_rect.setWidth(m_button.width());
    m_rect.setHeight(m_button.height());
    m_rect.moveTo(m_X,m_Y);
    pdpos = 0;
    pressed = 0;
    first_pressed = 0;
}
void Button::setposition(double x,double y){
    m_X = x - m_button.width()*0.5;
    m_Y = y - m_button.height()*0.5;
    m_rect.moveTo(x,y);
}
void Button::fall(int ntime){
    m_Y = FALL_SPEED*(ntime-m_time) + CHECKLINE_POS;
}
