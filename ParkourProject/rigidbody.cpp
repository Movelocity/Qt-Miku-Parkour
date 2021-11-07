#include "rigidbody.h"
///刚体
Rigidbody::Rigidbody(QRect rc){
    //保存QRect参数
    x = rc.x(), y = rc.y(), w = rc.width(), h = rc.height();
}


///*专为能动的物体设计*
void Rigidbody::update(int xx, int yy){
    x = xx, y = yy;
}


