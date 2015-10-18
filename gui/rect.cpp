#include "rect.h"
#include <QKeyEvent>


Rect::Rect()
{

}
 void Rect::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_Up){
        setPos(x()-10,y());

    }
 }

