#include "player.h"

#define rgBodyStartX 80
#define rgBodyStartY 60
#define rgBodyWidth 80
#define rgBodyHeight 165

Player::Player(){
    rd =Rigidbody(QRect(pos().x()+rgBodyStartX, pos().y()+rgBodyStartY, rgBodyWidth, rgBodyHeight));
    //自己的标签
    /*label = new QGraphicsTextItem(this);
    label->setPlainText("Text");
    label->setPos(x-5, y-15);*/
}

void Player::move(int dx, int dy){
    setPos(x()+dx, y()+dy);   
    if(offset==0) {
        rd.h=rgBodyHeight;
        rd.update(x()+rgBodyStartX, y()+rgBodyStartY);
    }
    else {
        rd.h=rgBodyHeight-offset;
        rd.update(x()+rgBodyStartX, y()+offset+rgBodyStartY);
    }
}

