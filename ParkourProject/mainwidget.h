#include <QWidget>
#include <QVBoxLayout>
#include "startpage.h"
#include "game.h"
class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
private slots:
    void playGame();
    void backToStart();
private:
    Game *game;
    StartPage *startPage;
};
