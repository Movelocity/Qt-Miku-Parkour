#include "button.h"
#include <QGraphicsRectItem>
#include <QDebug>

Button::Button(QString fileName)
{
    setPixmap(fileName);
}

Button::Button(QString img, QString img_on)
{
    pxmap = QPixmap(img);
    pxmapHover = QPixmap(img_on);
    //qDebug()<<"img: "<<img_on<<"\n\twidget;width:"<<pxmap.width()<<", height:"<<pxmap.height();
    setPixmap(img);
    hoverEn = true;
    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    if(hoverEn){
        setPixmap(pxmapHover);
        //qDebug()<<"enter";
    }
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    if(hoverEn){
        setPixmap(pxmap);
        //qDebug()<<"leave";
    }
}
