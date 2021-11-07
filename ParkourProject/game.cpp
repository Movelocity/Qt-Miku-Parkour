#include "game.h"
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QDebug>

#define BTNBase 860
#define BTNInterval 140
#define BTNTop 20

int groundBase = 570;
#define ROCKWRange 150
#define ROCKHRange 20
#define ROCKWMin 60
#define ROCKHMin 10
#define BGOffset 0
#define BoundaryLeft 0
#define BoundaryRight 1850
#define PlayerStartX 480
#define PlayerStartY 10
#define GROUNDWidth 2870

Game::Game(QObject *parent){
    //开始界面
    startSceneInit();
    //主界面
    mainSceneInit();
    aboutSceneInit();
    //先展示开始界面
    setScene(startScene);
    qDebug()<<"game constructed.";
}

void Game::keyPressEvent(QKeyEvent *e){
    if(inGame==false)return;
    //qDebug()<<"keyPressd";
    switch(e->key()){
    case Qt::Key_Left:
        playerState->keyListener(state::wleft);
        break;
    case Qt::Key_Right:
        playerState->keyListener(state::wright);
        break;
    case Qt::Key_Up:
        playerState->keyListener(state::wup);
        break;
    case Qt::Key_Down:
        playerState->keyListener(state::wdown);
        break;
    }
}

void Game::sceneUpdate(int x, int y){
    xPos+=x;
        player->move(x, y);//移动玩家
        //qDebug()<<"move";
        //game->player->label->setPlainText(QString::number(verSpeed)+QString("(%1, %2)").arg(game->player->x()).arg(game->player->y()));

    if(xPos>BoundaryLeft&&xPos<BoundaryRight){
        setSceneRect(xPos,yPos,WINDOW_WIDTH,WINDOW_HEIGHT);//移动视图
        //qDebug()<<game->sceneRect();

        //************背景移动****************//
        background1->setPos(xPos/5+BGOffset, yPos);

        //*********界面控件移动***********//
        playBtn->setPos(xPos+BTNBase, yPos+BTNTop);
        exitBtn->setPos(xPos+BTNBase+BTNInterval, yPos+BTNTop);
    }
}

///切换至主游戏界面
void Game::playGame()
{
    //展示主界面
    qDebug()<<"play game";
    inGame = true;
    qDebug()<<"animator begin";
    player->setPos(PlayerStartX, PlayerStartY);
    ground->setPos(30, groundBase);

    playBtn->setPos(BTNBase, BTNTop);
    exitBtn->setPos(BTNBase+BTNInterval, BTNTop);
    //构造函数未结束时初始化未完成，无法获取 pos() ，就只能在外面 setPos()
    initBlocks();//生成障碍物

    setFocus();
    setScene(mainScene);
    playerState->keyListener(wright);
}

///兼顾开始和结束游戏的函数
void Game::begin(){
    if(playerState->PlayState==false){
        playerState->begin();//状态机开启，里边也有些重置操作
        xPos = 0;
        playBtn->setPos(BTNBase, BTNTop);
        exitBtn->setPos(BTNBase+BTNInterval, BTNTop);
        background1->setPos(BGOffset, 0);
        Animatior->begin();
    }
    else{
        playerState->stop();
        Animatior->stop();
    }
}

void Game::startSceneInit(){
    QGraphicsPixmapItem *st_background = new QGraphicsPixmapItem(QPixmap(":/new/res/img/background.png"));
    QGraphicsPixmapItem *st_title = new QGraphicsPixmapItem(QPixmap(":/new/res/img/Parkour_text.png"));
    Button *startBtn = new Button(":/new/res/img/tx_start.png", ":/new/res/img/tx_start_on.png");
    Button *aboutBtn = new Button(":/new/res/img/tx_about.png", ":/new/res/img/tx_about_on.png");
    Button *quitBtn = new Button(":/new/res/img/tx_quit.png", ":/new/res/img/tx_quit_on.png");

    startScene = new QGraphicsScene(this);
    startScene->setSceneRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    startScene->addItem(st_background);
    startScene->addItem(st_title);
    startScene->addItem(startBtn);
    startScene->addItem(aboutBtn);
    startScene->addItem(quitBtn);
    st_background->setPos(0, 0);
    st_title->setPos(680, 250);
    startBtn->setPos(750, 350);
    aboutBtn->setPos(750, 450);
    quitBtn->setPos(750, 550);

    connect(startBtn, SIGNAL(clicked()), this, SLOT(playGame()));
    connect(aboutBtn, SIGNAL(clicked()), this, SLOT(showAboutScene()));
    connect(quitBtn, SIGNAL(clicked()), this, SLOT(close()));
    qDebug()<<"startScene added.";
}

void Game::mainSceneInit(){
    mainScene = new QGraphicsScene(this);
    player = new Player();                                              //添加Player
    qDebug()<<"player added.";

    background1 = new  QGraphicsPixmapItem();
    background1->setPixmap(QPixmap(":/m/img/mapRes/background1.png"));
    background1->setPos(BGOffset, 0);
     //*******************添加地面*******************//
    ground = new QGraphicsRectItem(0, 0, GROUNDWidth, 50);
    //地面刚体在方块初始化函数里

    //setRect初始化将item在其自身坐标系中设为（0，0），方便后面用 pos() 查看其场景坐标
    qDebug()<<"ground added.";

    //***************添加游戏界面、状态机、动画机*****************//
    mainScene->setSceneRect(0, 0, WINDOW_WIDTH*WIDTH_MUL, WINDOW_HEIGHT);
    playerState = new State(0, 0, WINDOW_WIDTH*WIDTH_MUL, WINDOW_HEIGHT);                                          //添加运动状态，额外传入mainScene的Rect值，方便点
    Animatior = new Animation();
    qDebug()<<"state added.";

    //***************实例化按钮们****************//
    playBtn = new Button(":/new/res/img/play1.png");
    exitBtn = new Button(":/new/res/img/close1.png");
    playBtn->setPos(860, 20);
    exitBtn->setPos(1000, 20);

    //view设置
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    mainScene->addItem(background1);
    mainScene->addItem(player);
    mainScene->addItem(ground);
    mainScene->addItem(playBtn);
    mainScene->addItem(exitBtn);

    connect(playBtn, SIGNAL(clicked()), this, SLOT(begin()));
    connect(exitBtn, SIGNAL(clicked()), this, SLOT(backToStart()));
    qDebug()<<"mainScene initalized.";
}

void Game::aboutSceneInit(){
    aboutScene = new QWidget(this);
    aboutScene->setVisible(false);
    aboutScene->setGeometry(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    QPalette pal(aboutScene->palette());
    pal.setColor(QPalette::Background, Qt::black);
    aboutScene->setAutoFillBackground(true);
    aboutScene->setPalette(pal);
    browser = new QTextBrowser(aboutScene);
    pushBtn = new QPushButton(aboutScene);
    layout = new QVBoxLayout(aboutScene);
    layout->addWidget(pushBtn);
    layout->addWidget(browser);
    pushBtn->setText("关闭");
    browser->setText("<html>"
                     "<body><h1><font size=\"36\">MikumikuParkour（测试版 1）</font></h1>"
                        "<div>"
                            "<p0><font size=\"10\">作者：Movelocity</font></p0>"
                            "<p><font size=\"10\">使用说明</font></p>"
                        "</div>"
                        "<div>"
                            "<img src=\":/new/res/img/demo1.png\"/>"
                        "</div>"
                        "<div>"
                            "<p1></p1>"
                            "<p2><font size=\"16\"><br/>&nbsp;↑跳跃<br/>&nbsp;↓滚翻<br/>&nbsp;←往左跑<br/>&nbsp;→往右跑</font></p2>"
                        "</div>"
                        "<div>"
                            "<img src=\":/new/res/img/demo2.png\">"
                            "<p3><font size=\"10\"><br/><br/>&nbsp;跑步过程中跳跃能跳得更远</font><br/></p3>"
                            "<img src=\":/new/res/img/demo3.png\">"
                            "<p4><font size=\"14\"><br/><br/>&nbsp;感谢您的使用</font><font size=\"12\"><br/>&nbsp;更多内容仍在开发中......</font></p4>"
                        "</div>"
                     "</body>"
                     "</html>");
    aboutScene->setLayout(layout);
    connect(pushBtn, SIGNAL(clicked()), this, SLOT(closeAboutScene()));
}

void Game::showAboutScene(){
    //setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    aboutScene->setVisible(true);
    aboutScene->show();
}

void Game::closeAboutScene(){
    //setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    //delete browser;
    //delete pushBtn;
    //delete layout;
    aboutScene->close();
    //delete aboutScene;
}
#include <QTime>
void Game::initBlocks(){
    //QBrush grassBrush;
    QBrush rockBrush;
    /*QLinearGradient linearGradient(400, 0, 400, 720);
    linearGradient.setColorAt(0.0, Qt::white);
    linearGradient.setColorAt(0.75, QColor("#ffeffd"));
    linearGradient.setColorAt(1.0, QColor("#cff3ff"));
    linearGradient.setSpread(QGradient::Spread::PadSpread);*/

    //grassBrush.setStyle(Qt::Dense1Pattern);
    rockBrush.setStyle(Qt::Dense1Pattern);
    QColor color1("#000009");//dark
    //QColor color2("#c4ffea");//blue
    //grassBrush.setColor(color2);
    rockBrush.setColor(color1);

    ground->setBrush(rockBrush);
    //mainScene->setBackgroundBrush(linearGradient);

    //*************初始固定黑方块*************//
    //QRect(10, 10, 128, 380)<<QRect(10, 500, 128, 400)管道，参数可能用得上
    blocks<<new Block(2, 245)<<new Block(0, 550)
         <<new Block(2, 850)<<new Block(0, 1200)<<new Block(2, 1500)<<new Block(2, 1628)
        <<new Block(2, 2000);
    rectList<<QRect(PlayerStartX+20, PlayerStartY+240, 220, 30);
    rectList<<QRect(30, groundBase-210, 128, 30)<<QRect(2300, groundBase-210, 256, 30);
    for (QList<Block*>::iterator ite = blocks.begin();ite!=blocks.end();ite++) {
        Barriers<<(**ite).rd;
        mainScene->addItem(*ite);
        (*ite)->setPos(QPoint((**ite).xx, (**ite).yy));
    }

    //地面刚体
    Barriers.append(Rigidbody(QRect(30, 570, GROUNDWidth, 50)));
    //边界
    rectList<<QRect(0, 0, 30, groundBase)<<QRect(GROUNDWidth+30, 0, 250, groundBase);

    //***********随机黑方块*******************//
    /*srand(QTime::currentTime().msec());
    for(int i=0, n=15; i<n; i++){
        rectList<<randomRectGenerate();
    }*/
    //************画出黑方块**************//
    foreach(QRect rct, rectList){
        QGraphicsRectItem *rect = new QGraphicsRectItem(rct);
        rectItemList<<rect;
        rect->setBrush(rockBrush);
        mainScene->addItem(rect);
        Barriers.append(Rigidbody(rct));
    }
    /*
    for(int i=0,n=rectList.size(); i<n; ++i){
        QGraphicsRectItem *rect = new QGraphicsRectItem(rectList[i]);
        rectItemList<<rect;
        rect->setBrush(rockBrush);
        mainScene->addItem(rect);
        Barriers.append(rectList[i]);
    }*/
}

QRect Game::randomRectGenerate(){
    return QRect(
                qrand()%WINDOW_WIDTH*WIDTH_MUL,
                qrand()%WINDOW_HEIGHT,
                qrand()%ROCKWRange+ROCKWMin,
                qrand()%ROCKHRange+ROCKHMin);
}

///回到开始界面
void Game::backToStart()
{
    //回来开始界面
    qDebug()<<"back";
    playerState->stop();
    Animatior->stop();
    inGame = false;
    setScene(startScene);
    //view rect
    setSceneRect(0, 0, 1080, 720);
    /*for(int i=0, n=rectItemList.size(); i<n; i++){
        mainScene->removeItem(rectItemList[i]);
    }*/
    mainScene->setItemIndexMethod(QGraphicsScene::NoIndex);

    for (QList<QGraphicsRectItem*>::iterator iter = rectItemList.begin(); iter!=rectItemList.end();iter++) {
        if((*iter)!=nullptr){
            mainScene->removeItem(*iter);
            delete(*iter);
            *iter = nullptr;
        }
    }
    for(QList<Block*>::iterator ite = blocks.begin(); ite!=blocks.end(); ite++){
        if((*ite)!=nullptr){
            mainScene->removeItem(*ite);
            delete (*ite);
            *ite = nullptr;
        }
    }
    /*foreach(QGraphicsRectItem *itm, rectItemList){
        if(itm->scene()==mainScene)    mainScene->removeItem(itm);
    }*/
    //clearList(rectList);
    rectList.clear();
    Barriers.clear();
    rectItemList.clear();
    blocks.clear();
    //clearList(rectItemList);
    /*foreach(QRect rc, rectList){
        rectList.removeOne(rc);
    }
    //clearList(Barriers);
    foreach(Rigidbody rc, Barriers){
        Barriers.removeOne(rc);
    }
    //clearList(rectItemList);
    foreach(QGraphicsRectItem *rc, rectItemList){
        rectItemList.removeOne(rc);
    }
    qDebug()<<"empty?: "<<rectList.isEmpty();*/
}

void Game::clearList(QList<QGraphicsRectItem*> list)
{
    foreach(QGraphicsRectItem* node, list){
        list.removeOne(node);
        delete node;
        node = nullptr;
    }
}
