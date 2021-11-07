#include "mainwidget.h"

#include <QDebug>
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("For Parkour");

    //startScene
    startPage = new StartPage;
    connect(startPage->startBtn, SIGNAL(clicked()), this, SLOT(playGame()));
qDebug()<<"page initialized";
    game = new Game;
    connect(game->exitBtn, SIGNAL(clicked()), this, SLOT(backToStart()));
qDebug()<<"game initialized";

    startPage->show();
    //close();
}

MainWidget::~MainWidget()
{
}

void MainWidget::playGame()
{
    //qDebug()<<"play";
    startPage->hide();
    game->show();
}

void MainWidget::backToStart()
{
    //qDebug()<<"back";
    game->hide();
    startPage->show();
}

