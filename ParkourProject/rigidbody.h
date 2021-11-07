#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#include <QRect>

class Rigidbody//可能要进行抽象设置了，因为隐形状态下无法获取碰撞item
{
public:
    Rigidbody(){};
    Rigidbody(QRect rc);
     void update(int x, int y);
     int x, y, w, h;

};

#endif // RIGIDBODY_H
