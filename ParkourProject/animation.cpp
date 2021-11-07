#include "animation.h"
#include "game.h"
#include "player.h"
#include "state.h"
#include <QDebug>
#include <QTimer>
extern Game *game;
Animation::Animation()
{
    init();
}

void Animation::begin()
{
    isPlaying = true;
    frame = 0;
    timer->start(100);
}

void Animation::stop()
{
    isPlaying = false;
    if(timer->isActive())
        timer->stop();
}

void Animation::init()
{
    fallingSheet = new SpriteSheet(":/charactor/sprites/falling.png", 3, 3);
    landSheet = new SpriteSheet(":/charactor/sprites/land.png", 3, 5);
    jumpSheet = new SpriteSheet(":/charactor/sprites/jump.png", 4, 5);
    runSheet = new SpriteSheet(":/charactor/sprites/run.png", 3, 4);
    run_to_stopSheet = new SpriteSheet(":/charactor/sprites/run_to_stop.png", 2, 4);
    stand_to_runSheet = new SpriteSheet(":/charactor/sprites/stand_to_run.png", 2, 2);
    idleSheet = new SpriteSheet(":/charactor/sprites/idle.png", 118, 1);
    rollSheet = new SpriteSheet(":/charactor/sprites/roll.png", 59, 1);
    image = idleSheet->tileAt(0);
    frame = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(play()));
}

void Animation::appendFrame(QImage img)
{

}

void Animation::appendFrames(QVector<QImage> imgs, int sum)
{

}

void Animation::playFinished()
{

}

void Animation::play()
{
    if(!isPlaying) return;
    state sta = game->playerState->getState();
    game->player->offset=0;//滚翻用的偏移
    switch(sta){
    case noState:
        game->playerState->setState(stand);
        break;
    case stand:
        if(lastState != stand) frame=0;
        image = idleSheet->tileAt(frame++);
        if(frame >= 118) frame=0;
        break;
    case standToRun:
        if(lastState !=standToRun) frame=0;
        image = stand_to_runSheet->tileAt(frame++);
        if(frame==4) game->playerState->setState(run);
        break;
    case run:
        if(lastState!=run) frame=0;
        image = runSheet->tileAt(frame++);
        if(frame==11) frame=0;
        break;
    case runToStop:
        if(lastState !=runToStop) frame=0;
        image = run_to_stopSheet->tileAt(frame++);
        if(frame==7) game->playerState->setState(stand);
        break;
    case jump:
        if(lastState != jump) frame=6;
        image = jumpSheet->tileAt(frame+=2);
        if(frame==16) game->playerState->setState(fall);
        break;
    case fall:
        if(lastState != fall) frame=0;
        image = fallingSheet->tileAt(frame++);
        if(frame==8) game->playerState->setState(fallLast);
        break;
    case fallLast:
        image = fallingSheet->tileAt(8);
    case land:
        if(lastState != land) frame=0;
        image = landSheet->tileAt(frame+=2);
        if(frame == 12) game->playerState->setState(stand);
        break;
    case roll:
        if(lastState != roll) frame=0;
        game->player->offset=70;//设置滚翻偏移
        image = rollSheet->tileAt(frame+=3);
        //切换状态
        if(frame==39&&game->playerState->prepareToJump){
            game->playerState->setState(jump);
            game->playerState->keyListener(wup);
            game->playerState->prepareToJump = 0;
        }
        else if(frame == 57) {
            game->playerState->setState(runToStop);
            sta = runToStop;//强行修改前状态，让下次切换开始帧换一下
            frame = 4;
        }
        break;
    default:;
    }
    lastState = sta;
    //qDebug()<<"frame:"<<frame<<"state:"<<sta;
    if(game->playerState->horDir == -1){
        image = image.mirrored(true, false);
    }
    game->player->setPixmap(QPixmap::fromImage(image));
    /*if(framesToPlay == 1){
        playFinished();//todo
    }*/
}
