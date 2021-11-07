#ifndef BUTTON_H
#define BUTTON_H
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
class Button : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Button(QString fileName);
    Button(QString img, QString img_on);
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *);
signals:
    void clicked();
private:
    bool hoverEn = false;
    QPixmap pxmap;
    QPixmap pxmapHover;
};

#endif // BUTTON_H
