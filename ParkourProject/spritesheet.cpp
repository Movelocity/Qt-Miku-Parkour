#include "spritesheet.h"
#include <QDebug>

#define spriteSize 240

SpriteSheet::SpriteSheet(QString filepath, int xSum, int ySum):xSum(xSum),ySum(ySum)
{
    img_.load(filepath);
}

QImage SpriteSheet::tileAt(int index)
{
    QRect tile(index%xSum*spriteSize, index/xSum*spriteSize, spriteSize, spriteSize);
    return img_.copy(tile);
}

QVector<QImage> SpriteSheet::tiles(int begin, int end)
{
    QVector<QImage> tiles;
    for(int i=begin; i<end; ++i){
        tiles.push_back(tileAt(i));
    }
    return tiles;
}
