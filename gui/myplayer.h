#ifndef MYPLAYER
#define MYPLAYER
#include <QGraphicsRectItem>
class MyPlayer: public QGraphicsRectItem{
public:
    void keyPressEvent(QKeyEvent *event);
};

#endif // MYPLAYER

