#ifndef STARTPAGE_H
#define STARTPAGE_H
#include <QGraphicsView>
//#include <QMouseEvent>
#include "button.h"

class StartPage : public QGraphicsView
{
public:
    StartPage(QObject *parent = 0);
    Button *startBtn;
public slots:

    //bool eventFilter(QObject *object, QEvent *event);
    //void Play();
private:
    QGraphicsScene *startScene;

};

#endif // STARTPAGE_H
