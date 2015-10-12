
#include "risk.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QDebug>

class MyPlayer: public QGraphicsRectItem{
    void keyPressEvent(QKeyEvent *event){
        qDebug() << "test";
    }
};



int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    //MainWindow mw;
    //mw.show();
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
