#include "block.h"
extern int groundBase;
Block::Block(int blockType, int startX){
    int blockWidth =128, blockHeight = 30;
    xx=startX, yy=groundBase;
    switch(blockType){
    case 0:
        img = QPixmap(":/m/img/mapRes/rock2.png");
        break;
    case 1:
        img = QPixmap(":/m/img/mapRes/rock1.png");
        break;
    case 2:
        img = QPixmap(":/m/img/mapRes/frame1.png");
        break;
    default:
        img = QPixmap("/m/img/mapRes/rock2.png");;
    }
    yy -= img.height();
    rd = Rigidbody(QRect(startX, yy, blockWidth, blockHeight));
    setPixmap(img);
}

Block::Block(int blockType, int startX, int startY){
    int blockWidth =128, blockHeight = 30;
    xx=startX, yy=startY;
    switch(blockType){
    case 0:
        img = QPixmap(":/m/img/mapRes/rock2.png");
        break;
    case 1:
        img = QPixmap(":/m/img/mapRes/rock1.png");
        break;
    case 2:
        img = QPixmap(":/m/img/mapRes/frame1.png");
        break;
    default:
        img = QPixmap("/m/img/mapRes/rock2.png");;
    }

        rd = Rigidbody(QRect(startX, startY, blockWidth, blockHeight));
        setPixmap(img);
}
