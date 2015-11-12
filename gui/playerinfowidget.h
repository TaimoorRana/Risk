#ifndef PLAYERINFOWIDGET_H
#define PLAYERINFOWIDGET_H

#include <QWidget>
#include "map_scene.h"
#include "player.h"
#include"player_observer.h"

namespace Ui {
class PlayerInfoWidget;
}

class PlayerInfoWidget : public QWidget, public PlayerObserver
{
	Q_OBJECT

public:
	explicit PlayerInfoWidget(QWidget *parent = 0, Player* subject = 0, MapScene *scene = 0);
	~PlayerInfoWidget();
	void update();

private:
	Ui::PlayerInfoWidget *ui;
	Player* player;
	MapScene* scene;
};

#endif // PLAYERINFORWIDGET_H
