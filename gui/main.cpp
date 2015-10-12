
#include "risk.h"
#include "myplayer.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QDebug>



int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    QGraphicsScene *scene = new QGraphicsScene();
    MyPlayer *player =  new MyPlayer;
    player->setRect(0,0,100,100);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);
    QGraphicsView *view = new QGraphicsView(scene);
    view->show();

    return application.exec();
}
