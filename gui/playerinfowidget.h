#ifndef PLAYERINFOWIDGET_H
#define PLAYERINFOWIDGET_H

#include <QWidget>
#include "player.h"
#include"player_observer.h"

namespace Ui {
class PlayerInfoWidget;
}

class PlayerInfoWidget : public QWidget, public PlayerObserver
{
	Q_OBJECT

public:
	explicit PlayerInfoWidget(QWidget *parent = 0, Player* subject = 0);
	~PlayerInfoWidget();
	void update();

private:
	Ui::PlayerInfoWidget *ui;
	Player* player;
};

#endif // PLAYERINFORWIDGET_H
