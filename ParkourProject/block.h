#ifndef BLOCK_H
#define BLOCK_H
#include <QGraphicsPixmapItem>
#include <rigidbody.h>
class Block: public QGraphicsPixmapItem
{
public:
    Block(){};
    Block(int blockType, int startX);
    Block(int blockType, int startX, int startY);
    QPixmap img;
    Rigidbody rd;
    int xx, yy;
};

#endif // BLOCK_H
