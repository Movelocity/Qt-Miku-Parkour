#ifndef GAME_H
#define GAME_H
#include <QGraphicsView>
#include "rigidbody.h"
#include "animation.h"
#include "state.h"
#include "player.h"
#include "button.h"
#include <block.h>
#include <QWidget>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QPushButton>

#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1080
#define WIDTH_MUL 5
class Game : public QGraphicsView
{
    Q_OBJECT
public:
    //constructor
    Game(QObject *parent = 0);
    void keyPressEvent(QKeyEvent *);
    Player *player;
    QGraphicsScene *mainScene;
    QGraphicsRectItem *ground;
    QList<Rigidbody> Barriers;
    //Rigidbody *playerBody;
    State *playerState;
    ///更新界面位置，玩家位置，以及界面基础控件位置
    /// 水平方向都有移动x，y只会移动玩家位置
    void sceneUpdate(int x, int y);
public slots:
    void backToStart();
    void playGame();
    void begin();
    void showAboutScene();
    void closeAboutScene();
private:
     QGraphicsScene *startScene;
     ///这个是一个QWidget，不是实际的scene
     QWidget *aboutScene;
     void startSceneInit();
     void mainSceneInit();
     void aboutSceneInit();
     bool inGame = false;
     void initBlocks();
     QRect randomRectGenerate();
     QList<QRect> rectList;
     QList<QGraphicsRectItem*> rectItemList;
     QList<Block*> blocks;
     void clearList(QList<QGraphicsRectItem*> list);
     Animation *Animatior;

    Button *playBtn;
    Button *exitBtn;

    int xPos = 0;
    int yPos = 0;

    QGraphicsPixmapItem* background1;
     ///belong to start scene
     /*QGraphicsTextItem *playText;
     QGraphicsTextItem *aboutText;
     QGraphicsTextItem *quitText;
     */
    QVBoxLayout *layout;
    QTextBrowser *browser;
    QPushButton *pushBtn;
};

#endif // GAME_H
