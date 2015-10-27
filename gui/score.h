#include <QGraphicsTextItem>


#ifndef SCORE
#define SCORE

class Score: public QGraphicsTextItem{
public:
    Score(QGraphicsItem* parent=0, int score = 0);
    void addScore();
    int getScore();
private:
    int score;
};


#endif // SCORE

