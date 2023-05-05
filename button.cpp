#include "button.h"
#include "config.h"

Button::Button(int m_time,int endtime):m_time(m_time),endtime(endtime)
{
    m_button.load(BUTTON_PATH);
    m_X = GAME_WIDTH*0.5 - m_button.width()*0.5;
    m_Y = 0 - m_button.height()*0.5;
    m_rect.setWidth(m_button.width());
    m_rect.setHeight(m_button.height());
    m_rect.moveTo(m_X,m_Y);
}
void Button::setposition(int x,int y){
    m_X = x - m_button.width()*0.5;
    m_Y = y - m_button.height()*0.5;
    m_rect.moveTo(x,y);
}
void Button::fall(int ntime){
    m_Y = CHECKLINE_POS+(ntime-m_time)*FALL_SPEED;
}
