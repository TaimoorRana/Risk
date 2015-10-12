#include "myplayer.h"
#include <QGraphicsRectItem>
#include <QDebug>
#include <QKeyEvent>

void MyPlayer::keyPressEvent(QKeyEvent *event){
    qDebug() << event->key();
}
