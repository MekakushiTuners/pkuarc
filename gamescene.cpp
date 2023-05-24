#include "gamescene.h"
#include "config.h"
#include "qicon.h"
#include "qpainter.h"
#include "qtimer.h"
#include "QKeyEvent"
#include <QPainter>
#include <QFont>
#include <QRectF>
#include <QFontMetrics>
#include <QString>
#include <QMediaPlayer>
#include <QJsonArray>
#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <utils.h>

using namespace std;
gamescene::gamescene(QWidget *parent)
    : QWidget(parent)
{

}

gamescene::~gamescene()
{

}

void gamescene::initscene(){
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    setWindowTitle(GAME_TITLE);
    setWindowIcon(QIcon(GAME_ICON));
    m_timer.setInterval(GAME_RATE);
    setFocusPolicy(Qt::StrongFocus);
    checktype = 0;
    checkimage[1].load(ICON_PERFECT_PATH);
    checkimage[2].load(ICON_GREAT_PATH);
    checkimage[3].load(ICON_GOOD_PATH);
    checkimage[4].load(ICON_MISS_PATH);
    background.load(GAME_BACKGROUND_PATH);
    background = background.scaled(1.6*background.width(),1.6*background.height(),Qt::KeepAspectRatio);
    combo = 0;
    drawtext(label[0],QFont("Exo", 40, false, false),1610,550,"Combo");
    drawtext(label[1],QFont("Exo", 40, false, false),1610,750,"           ");
}
int timeshift = 0;
int calctime(int a0,int a1,int a2,double bpm){
    //printf("%.5f\n",(((double)(a1))/a2 + a0) / bpm);
    return (int)((((double)(a1))/a2 + a0) * 60 / bpm * 1000) + timeshift;
}
void gamescene::playGame(){
    tottime.start();
    //static int ntime = 0; // ms
    m_track[0].setposition(960-360,0);
    m_track[1].setposition(960-120,0);
    m_track[2].setposition(960+120,0);
    m_track[3].setposition(960+360,0);
    QFile file(songs[songnumber].mcpath);
    file.open(QIODevice::ReadOnly);
    QByteArray data=file.readAll();
    file.close();
    QJsonParseError parseError;
    QJsonDocument doc=QJsonDocument::fromJson(data,&parseError);
    if(parseError.error!=QJsonParseError::NoError){
        return;
    }
    QJsonObject obj = doc.object();
    QJsonArray time = obj["time"].toArray();
    double pbpm = 1;
    int ptime = 0;
    vector<pair<int,double> > v;
    for(int i = 0;i< time.size();i++){
        QJsonObject timei = time.at(i).toObject();
        QJsonArray beat = timei["beat"].toArray();
        int b0 = beat.at(0).toInt(),b1 = beat.at(1).toInt(),b2 = beat.at(2).toInt();
        double bpm = timei["bpm"].toDouble();
        int ntime = calctime(b0,b1,b2,pbpm);
        int ts = ntime;
        v.push_back({ntime,bpm});
        printf("%d %f\n",ntime,bpm);
        pbpm = bpm;
        timeshift = 0;
        timeshift = ts - calctime(b0,b1,b2,pbpm);
        //printf("%d %d %d\n",timeshift,ts);


    }


    QJsonArray note = obj["note"].toArray();
    QJsonObject lst = note[note.size()-1].toObject();
    int offset = WAIT_TIME + lst["offset"].toInt();
    int bpmpos = 1;
    double bpm = v[0].second;
    timeshift = 0;
    for(int i=0;i<note.size()-1;i++){
        QJsonObject now = note[i].toObject();
        QJsonArray beat = now["beat"].toArray();
        int b0 = beat.at(0).toInt(),b1 = beat.at(1).toInt(),b2 = beat.at(2).toInt();
        int st = calctime(b0,b1,b2,bpm); //ms
        if(bpmpos < v.size() && st >= v[bpmpos].first){
            int tmptime = st;
            bpm = v[bpmpos].second;
            bpmpos++;
            timeshift = 0;
            timeshift = tmptime - calctime(b0,b1,b2,bpm);
        }
        int col = now["column"].toInt();
        vector<int> pdtime;
        if(now.keys().count() == 3){
            QJsonArray endbeat = now["endbeat"].toArray();
            int e0 = endbeat.at(0).toInt(),e1 = endbeat.at(1).toInt(),e2 = endbeat.at(2).toInt();
            int ed = calctime(e0,e1,e2,bpm);
            int tmp = b0;
            while(tmp<e0){
                pdtime.push_back(offset + calctime(tmp,b1,b2,bpm));
                tmp++;
            }
            pdtime.push_back(ed);
            m_track[col].push_button(Button(offset + st,offset + ed,pdtime));
        }else{
            m_track[col].push_button(Button(offset + st, offset + st, pdtime));
        }
    }

/*
    for(int i=0;i<1;i++)
        for(int j=1;j<=1;j++){
            vector<int> pdtime;
                pdtime.push_back(2734);
                m_track[i].push_button(Button(2463,2734,pdtime));

        }*/


    QMediaPlayer *player = new QMediaPlayer;
    player -> setMedia(QUrl(songs[songnumber].path)); // 添加要播放的音乐文件
    player -> setVolume(100);



    for(int i=0;i<4;i++)
        connect(&m_track[i],&Track::checksignal,this,&gamescene::checkslot);

    //while(tottime.elapsed()<1500);

    player -> play();
    m_timer.start();
    tottime.restart();
    connect(&m_timer,&QTimer::timeout,[=](){
        //ntime += GAME_RATE;
        updateStatus(tottime.elapsed());
        update();
    });
}
void gamescene::checkslot(int m_type){
    checktype = m_type;
    if(m_type <=3) combo++;
    else combo = 0;
    label[1].setText(QString::number(combo));
}
void gamescene::openslot(int sn){
    songnumber = sn;
    initscene();
    //printf("%d\n",1);
    show();
    playGame();
}
void gamescene::updateStatus(int ntime){
    for(int i=0;i<4;i++)
        m_track[i].uptateStatus(ntime);
}
void gamescene::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    //label[1].setText(QString(combo,10));
    //label[1].show();
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QColor(57, 175, 213));
    painter.drawLine(QPointF(0, CHECKLINE_POS), QPointF(GAME_WIDTH, CHECKLINE_POS)); // draw checkline
    painter.setPen(QColor(0, 0, 0));
    for(int i=0;i<4;i++)
        m_track[i].drawtrack(painter);
    if(checktype){
        painter.drawPixmap(1560,240,checkimage[checktype]);
    }

}
void gamescene::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key_A:
            m_track[0].onpressed(tottime.elapsed());
            break;
        case Qt::Key_S:
            m_track[1].onpressed(tottime.elapsed());
            break;
        case Qt::Key_K:
            m_track[2].onpressed(tottime.elapsed());
            break;
        case Qt::Key_L:
            m_track[3].onpressed(tottime.elapsed());
            break;
    }
}
void gamescene::keyReleaseEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key_A:
            m_track[0].onreleased(tottime.elapsed());
            break;
        case Qt::Key_S:
            m_track[1].onreleased(tottime.elapsed());
            break;
        case Qt::Key_K:
            m_track[2].onreleased(tottime.elapsed());
            break;
        case Qt::Key_L:
            m_track[3].onreleased(tottime.elapsed());
            break;
    }
}
