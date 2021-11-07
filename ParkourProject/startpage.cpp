#include "startpage.h"
#include <QGraphicsRectItem>
//#include<QGraphicsSceneMouseEvent>

//#include <QGraphicsScene>
StartPage::StartPage(QObject *parent)
{

    startBtn = new Button;
    startBtn->setRect(50, 50, 360, 240);

    //startBtn->installSceneEventFilter(startBtn);
    QGraphicsScene *startScene = new QGraphicsScene(this);
    startScene->setSceneRect(0, 0, 1080, 720);
    setScene(startScene);
    startScene->addItem(startBtn);
}

/*bool StartPage::eventFilter(QObject *object, QEvent *event)
{
    return 1;
}*/
