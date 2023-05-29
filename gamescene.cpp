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
#include <QFontDatabase>
#include <mainscene.h>
#include <resultscene.h>

using namespace std;
gamescene::gamescene(QWidget *parent)
    : QWidget(parent)
{

}

gamescene::~gamescene()
{

}

void gamescene::initscene(){
    setAttribute(Qt::WA_DeleteOnClose);
    for(int i=0;i<font_size;i++) QFontDatabase::addApplicationFont(font_path[i]);
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    setWindowTitle(GAME_TITLE);
    setWindowIcon(QIcon(GAME_ICON));
    m_timer.setInterval(GAME_RATE);
    setFocusPolicy(Qt::StrongFocus);
    track_bg.load(TRACK_BG_PATH);
    checkimage[1][0].load(ICON_PERFECT_PATH);
    checkimage[2][0].load(ICON_GREAT_PATH);
    checkimage[3][0].load(ICON_GOOD_PATH);
    checkimage[4][0].load(ICON_MISS_PATH);
    for(int i=1;i<=4;i++){
        scaling_pix(checkimage[i][0],1.3);
    }
    for(int i=1;i<=31;i++){
        for(int j=1;j<=4;j++){
            checkimage[j][i] = checkimage[j][0];
            scaling_pix(checkimage[j][i],0.005*i+1);
        }
    }
    background.load(GAME_BACKGROUND_PATH);
    pausebutton.load(Pausebutton_PATH);
    bottomline.load(BOTTOM_LINE_PATH);
    scaling_pix(bottomline,1024.0/bottomline.width()-0.017);
    pausebg.load(Pausebg_PATH);
    scaling_pix(pausebg,1.55);
    uileft.load(Uileft_PATH);
    uiright.load(Uiright_PATH);
    scaling_pix(uiright,0.9);
    scaling_pix(background,1.6);
    setpix(&label[2],uileft,uileft.width()/2,20+uileft.height()/2);
    connect(&label[2],&QLabel_C::clicked,this,&gamescene::pause);
    setpix(&label[3],uiright,1920-uiright.width()/2,20+uiright.height()/2);
    //setpix(&label[10],bottomline,960,CHECKLINE_POS);
    //drawtext(&label[0],QFont("Exo", 40, false, false),960,550,"Combo");
    drawtext(&label[1],QFont("Exo", 40, false, false),960,550,"           ");
    opacityEffect[1].setOpacity(0.3);
    label[1].setGraphicsEffect(&opacityEffect[1]);
    startcount.setInterval(3000);
    endtimer.setInterval(1000);
}
int timeshift = 0;
int calctime(int a0,int a1,int a2,double bpm){
    //printf("%.5f\n",(((double)(a1))/a2 + a0) / bpm);
    return (int)((((double)(a1))/a2 + a0) * 60 / bpm * 1000) + timeshift;
}
void gamescene::playGame(){
    tottime.start();startcount.start();bgtimer.start();
    bg_y = 0;combo = 0;checktype = 0;totcount = 0;ptime = 0;pausetime = 0;paused = 0;started = 0;ended = 0;pause_seted = 0;maxcombo = 0;
    for(int i=0;i<=3;i++) m_track[i].clear();
    smallbase.load(songs[songnumber].base);
    scaling_pix(smallbase,0.25);
    //static int ntime = 0; // ms
    m_track[0].setposition(960-360,0);
    m_track[1].setposition(960-120,0);
    m_track[2].setposition(960+120,0);
    m_track[3].setposition(960+360,0);
    for(int i=1;i<=4;i++) count[i] = 0;
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
        //printf("%d %f\n",ntime,bpm);
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
                totcount++;
            }
            pdtime.push_back(ed);totcount++;
            m_track[col].push_button(Button(offset + st,offset + ed,pdtime));
        }else{
            totcount++;
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


    player = new QMediaPlayer;
    player -> setMedia(QUrl(songs[songnumber].path)); // 添加要播放的音乐文件
    player -> setVolume(100);



    for(int i=0;i<4;i++)
        connect(&m_track[i],&Track::checksignal,this,&gamescene::checkslot);

    //while(tottime.elapsed()<1500);


    connect(&startcount,&QTimer::timeout,[=](){
        if(!paused){
            started = 1;
            player -> play();
            m_timer.start();
            tottime.restart();
            startcount.stop();
        }

    });
    connect(&endtimer,&QTimer::timeout,[=](){
        //printf("endtimerended\n");
        resultscene* res = new resultscene;
        res->openslot(songnumber,getintscore(),maxcombo,count[1]+count[2],count[3],count[4]);
        QTime dieTime = QTime::currentTime().addMSecs(5);
        while( QTime::currentTime() < dieTime ) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        close();
        endtimer.stop();
    });
    connect(&bgtimer,&QTimer::timeout,[=](){
        //ntime += GAME_RATE;
        updatebg(gettime());
        update();
    });
    connect(&m_timer,&QTimer::timeout,[=](){
        //ntime += GAME_RATE;
        updateStatus(gettime());
        update();
    });
}
void gamescene::checkslot(int m_type){
    count[m_type]++;
    checktype = m_type;
    if(m_type <=3) combo++;
    else combo = 0;
    maxcombo = combo>maxcombo?combo:maxcombo;
    label[1].setText(QString::number(combo));
    ptime = gettime();
}
void gamescene::back_to_main(){
    mainscene* ms = new mainscene;
    ms -> open_with_shutter();
   // if(player!=NULL) delete player;
    if(player) player->stop();
    QTime dieTime = QTime::currentTime().addMSecs(5);
    while( QTime::currentTime() < dieTime ) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    close();
//    dieTime = QTime::currentTime().addMSecs(100);
//    while( QTime::currentTime() < dieTime ) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
//    delete this;
}
void gamescene::openslot(int sn){
    songnumber = sn;
    initscene();
    //printf("%d\n",1);
    show();
    playGame();
}
void gamescene::updatebg(int ntime){
    bg_y = -ntime%track_bg.height();
}
void gamescene::updateStatus(int ntime){
    if(count[1]+count[2]+count[3]+count[4] == totcount&&!ended){
        endtimer.start();ended = 1;
        //printf("endtimerstarted\n");
    }
    for(int i=0;i<4;i++)
        m_track[i].uptateStatus(ntime);
}
void gamescene::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    //label[1].setText(QString(combo,10));
    //label[1].show();
    drawpix_inmiddle(painter,background,960,540);
    painter.setRenderHint(QPainter::Antialiasing, true);
    int ny = bg_y;
    while(ny < 1080){
        drawpix_inmiddle(painter,track_bg,960,ny+track_bg.height()/2);
        ny += track_bg.height();
    }
//    painter.setPen(QColor(57, 175, 213));
//    painter.drawLine(QPointF(0, CHECKLINE_POS), QPointF(GAME_WIDTH, CHECKLINE_POS)); // draw checkline
//    painter.setPen(QColor(0, 0, 0));
    drawpix_inmiddle(painter,bottomline,960,CHECKLINE_POS);
    for(int i=0;i<4;i++)
        m_track[i].drawtrack(painter);
    int ntime = gettime();
    if(checktype){
        if(ntime - ptime > 30){
            opacityEffect[2].setOpacity((1.0 - 0.002*(ntime - ptime))>0?(1.0 - 0.002*(ntime - ptime)):0);
            label[4].setGraphicsEffect(&opacityEffect[2]);
            setpix(&label[4],checkimage[checktype][0],960,660);
        }
        else{
            opacityEffect[2].setOpacity((1.0 - 0.002*(ntime - ptime))>0?(1.0 - 0.002*(ntime - ptime)):0);
            label[4].setGraphicsEffect(&opacityEffect[2]);
            setpix(&label[4],checkimage[checktype][(30-(ntime - ptime))],960,660+1*(30-(ntime - ptime)));
        }
    }
    string score = getscore();
    drawtext_with_shadow(&label[5],&shadow[5],QFont("Exo", 36, false, false),1680,95,score);
    drawtext_with_shadow(&label[6],&shadow[6],QFont("NanumBarunGothicOTF", 11, false, false),1840,163,"Future "+to_string(songs[songnumber].difficulty));
    setpix(&label[7],smallbase,1510,230);
    drawtext_left_with_shadow(&label[8],&shadow[8],QFont("NanumBarunGothicOTF", 13, false, false),1600,215,songs[songnumber].name.toStdString());
    drawtext_left_with_shadow(&label[9],&shadow[9],QFont("NanumBarunGothicOTF", 11, false, false),1600,255,songs[songnumber].writer.toStdString());

}
void gamescene::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key_A:
            m_track[0].onpressed(gettime());
            break;
        case Qt::Key_S:
            m_track[1].onpressed(gettime());
            break;
        case Qt::Key_K:
            m_track[2].onpressed(gettime());
            break;
        case Qt::Key_L:
            m_track[3].onpressed(gettime());
            break;
    }
}
void gamescene::keyReleaseEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key_A:
            m_track[0].onreleased(gettime());
            break;
        case Qt::Key_S:
            m_track[1].onreleased(gettime());
            break;
        case Qt::Key_K:
            m_track[2].onreleased(gettime());
            break;
        case Qt::Key_L:
            m_track[3].onreleased(gettime());
            break;
    }
}
