#include "score.h"
#include <QFont>

Score::Score(QGraphicsItem *parent, int score): QGraphicsTextItem(parent)
{
    this->score = score;
    setPlainText(QString("Score: ") + QString::number(score));
    setDefaultTextColor(Qt::blue);
    setFont(QFont("times",16));
}

void Score::addScore()
{
    score++;
    setPlainText(QString("Score: ") + QString::number(score));
}

int Score::getScore()
{
    return score;
}
