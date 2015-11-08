#ifndef PLAYERINFORWIDGET_H
#define PLAYERINFORWIDGET_H

#include <QWidget>

namespace Ui {
class PlayerInforWidget;
}

class PlayerInforWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerInforWidget(QWidget *parent = 0);
    ~PlayerInforWidget();

private:
    Ui::PlayerInforWidget *ui;
};

#endif // PLAYERINFORWIDGET_H
