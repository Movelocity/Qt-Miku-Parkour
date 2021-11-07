#include "game.h"
//game.h里面有头文件全家桶1了
#include <QDebug>
#include <QList>
//#include <QGraphicsLineItem>//用于提前检测位移与碰撞

extern Game *game;

State::State(int sx, int sy, int sw, int sh){
    scx=sx,scy=sy,scw=sw,sch=sh;//得到场景rect

    updateTimer = new QTimer(this);
    qDebug()<<"timer applied.";
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(update()));
    qDebug()<<"connected.";

    horSpeed = 0;//先简单粗暴地设置跑动速度
}

void State::setState(state newState){
    currentState = newState;
}

void State::keyListener(int key)
{
    switch(key){
    case state::wleft:
        if(currentState!=run && landing==1 && currentState!=roll) currentState = standToRun;
        horDir = -1;
        if(landing == 1)horSpeed = 20;                //在空中就别手动加速了//不动会被卡在坑里啊
        else if(horSpeed==0)horSpeed = 5;         //这行是为了能在空中微挪 上台阶
        countDown=4;
        break;
    case state::wright:
        if(currentState!=run && landing==1&& currentState!=roll) currentState = standToRun;
        horDir = 1;
        if(landing == 1)horSpeed = 20;
        else if(horSpeed==0)horSpeed = 5;
        countDown=4;
        break;
     case state::wup:
        if(currentState==roll) {
            prepareToJump = 1;
            break;
        }
        if(landing){
            currentState = jump;
            verSpeed -=35;
        }
        if(horSpeed ==20)horSpeed+=5;//跑起来跳得更远
        landing = 0;
        countDown = 99999;
        break;
    case state::wdown:
        if(currentState!=roll  && (landing==1 || vdistance<100)) {
            currentState = roll;
        }
        if(horSpeed>=20&&horSpeed<=26) horSpeed = 26;
        else horSpeed +=10;
        break;
    }
}

state State::getState(){
    return currentState;
}

void State::begin(){   
        //game->sceneUpdate(-game->pos().x()+WINDOW_WIDTH, 0);
        game->setSceneRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        game->player->setPos(480, 10);
        setState(stand);
        updateTimer->start(100);
        PlayState = true;
        qDebug()<<"started.";
}

void State::stop()
{
    updateTimer->stop();
    qDebug()<<"stopped.";
    PlayState = false;
}
///excuted at every frame.  Judge the collision and move player
void State::update(){
    if(countDown>0)countDown--;
    else{
        if(currentState==state::run){
            setState(state::runToStop);
            horSpeed = 10;
        }
        else if(currentState==state::stand)horSpeed=0;
    }

    //纵向考虑重力，横向考虑碰撞
    Rigidbody pl = game->player->rd;
    vdistance = WINDOW_HEIGHT;//暂时最高这么高
    int hdistance = WINDOW_WIDTH;
    //foreach(Rigidbody rrr, game->Barriers){   }

    for(int i=0, n=game->Barriers.size(); i<n; ++i){
        Rigidbody bar = game->Barriers[i];
        /*****看脚下*****/
        if(pl.x+pl.w>=bar.x && pl.x<=bar.x+bar.w){//有无在相同x区间内的刚体
            if(pl.y+pl.h < bar.y+bar.h){                  // "+bar.h" 防止遁地
                int newDistance = bar.y-pl.y-pl.h;   //有就看脚下多远是那个刚体
                if(newDistance>-5 && newDistance<vdistance){
                    vdistance = newDistance;             //如此找出与脚下最近的刚体距离
                    //绕的有点乱，目前能用了
                }
            }
        }
        /*****看前后****/
        //if((bar.y>pl.y&&bar.y<=pl.y+pl.h) || (bar.y+bar.h>pl.y&&bar.y+bar.h<pl.y+pl.h)){//在y区间能撞到的刚体
        if(       (bar.y>pl.y&&bar.y<pl.y+pl.h)
                || (bar.y+bar.h>pl.y&&bar.y+bar.h<pl.y+pl.h)
                || (pl.y>bar.y&&pl.y<bar.y+bar.h)
                || (pl.y+pl.h<bar.y&&pl.y+pl.h>bar.y+bar.h)){//在y区间能撞到的刚体
            if(horDir==1 && pl.x+pl.w<bar.x+bar.w){                                    //看方向，并防止穿墙
                 int newDistance = bar.x-pl.x-pl.w;                                           //看前面多远是当前扫描的刚体
                 if(newDistance>-10 && newDistance<hdistance)                    //找出前方最近刚体
                     hdistance = newDistance;
                 if(bar.y==pl.y+pl.h && pl.x+pl.w==bar.x)//把玩家往后挪一点, 不然会卡bug
                     game->player->move(-1, 0);
            }
            else if(horDir==-1){                                                                       //左边同理
                int newDistance = pl.x-bar.x-bar.w;
                if(newDistance>-10 && newDistance<hdistance)
                    hdistance = newDistance;
                if(bar.y==pl.y+pl.h && pl.x==bar.x+bar.w)//把玩家往后挪一点, 不然会卡bug
                    game->player->move(1, 0);
            }
        }
    }
        //着陆
        //qDebug()<<"distance: "<<vdistance<<"    verSpeed: "<<verSpeed;
        //static int cou=0;
        if(verSpeed<vdistance){
            verSpeed += 6;
            if(currentState==stand) setState(fall);
            //qDebug()<<"fall"<<cou++;
        }
        else{
            game->player->move(0, vdistance);
            verSpeed = 0;
            if(!landing){                   //状态为未着陆
                horSpeed = 15;
                countDown = 4;
                landing = 1;                //状态变为着陆
                if(currentState==fall || currentState==jump)setState(land);
            }
        }
        if(landing==1 && currentState==fallLast) setState(land);
        //防止穿墙
        if(hdistance<horSpeed){
            game->player->move(hdistance*horDir, 0);
            horSpeed=0;
            if(currentState==run) setState(runToStop);
            else if(currentState==roll){
                //todo: add speed
            }
        }
        //qDebug()<<"distance: "<<hdistance<<"  horSpeed: "<<horSpeed;
        //更新位置
        game->sceneUpdate(horSpeed*horDir, verSpeed);
}
