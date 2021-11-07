#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsTextItem>
#include "rigidbody.h"
class Player : public QGraphicsPixmapItem
{
public:
    Player();
    QImage img;
    Rigidbody rd;
    QGraphicsTextItem *label;
    void move(int x, int y);
    int xx, yy, ww, hh;
    ///滚翻专用--竖直偏移量
    int offset = 0;
};

#endif // PLAYER_H
