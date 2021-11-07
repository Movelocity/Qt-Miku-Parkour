#ifndef STATE_H
#define STATE_H
#include <QString>
#include <QTimer>

enum state{
    noState,
    wleft,
    wright,
    wup,
    wdown,
    stand,
    standToRun,
    run,
    runToStop,
    jump,
    fall,
    fallLast,
    land,
    roll,
};

class State : public QObject
{
    Q_OBJECT
public:
    State(int sx, int sy, int sw, int sh);
    void setState(state move);
    void keyListener(int key);
    state getState();
    int horDir = 1;     //方向
    bool PlayState = false;
    bool prepareToJump = 0;
public slots:
    void begin();//开始动画
    void stop();
private:
    QTimer *updateTimer;
    //QTimer *countDown;
    int countDown = 0;
    ///1 on ground; 0 in the air
    int landing = 0;

    int horSpeed = 0;//标量
    state currentState = noState;
    int verSpeed = 0;//矢量
    int vdistance = 0;
    ///场景rect
    int scx, scy, scw, sch;


private slots:
    void update();
};

#endif // STATE_H
