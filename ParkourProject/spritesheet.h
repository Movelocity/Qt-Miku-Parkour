#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <QObject>
#include <QVector>
#include <QPixmap>

class SpriteSheet : public QObject
{
    Q_OBJECT
public:
    SpriteSheet(QString filepath, int xSum, int ySum);
    QImage tileAt(int index);
    QVector<QImage> tiles(int begin, int end);
private:
    QImage img_;
    int xSum;
    int ySum;
};

#endif // SPRITESHEET_H
