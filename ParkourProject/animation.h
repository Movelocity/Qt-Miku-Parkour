#ifndef ANIMATION_H
#define ANIMATION_H

#include <QObject>
#include "spritesheet.h"

class Animation : public QObject
{
    Q_OBJECT
public:
    Animation();
    void begin();
    void stop();
public slots:
    void play();
private:
    void init();
    void appendFrame(QImage img);
    void appendFrames(QVector<QImage> imgs, int sum);
    void playFinished();
    QTimer *timer;
    int frame;
    int framesToPlay;
    int framesPlayed;
    bool isPlaying = false;
    QImage image;
    SpriteSheet *runSheet;
    SpriteSheet *idleSheet;
    SpriteSheet *run_to_stopSheet;
    SpriteSheet *stand_to_runSheet;
    SpriteSheet *jumpSheet;
    SpriteSheet *fallingSheet;
    SpriteSheet *landSheet;
    SpriteSheet *rollSheet;
    int lastState;
};

#endif // ANIMATION_H
