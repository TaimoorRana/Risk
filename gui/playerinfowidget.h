#ifndef PLAYERINFOWIDGET_H
#define PLAYERINFOWIDGET_H

#include <QWidget>
#include "map_scene.h"
#include "player.h"
#include "playerstatusindicator.h"

namespace Ui {
class PlayerInfoWidget;
}

class PlayerInfoWidget : public QWidget, public Observer
{
	Q_OBJECT

public:
	explicit PlayerInfoWidget(QWidget *parent = 0, Player* subject = 0, MapScene *scene = 0);
	~PlayerInfoWidget();
	void observedUpdated();

private:
	Ui::PlayerInfoWidget *ui;
	Player* player;
	MapScene* scene;
	PlayerStatusIndicator* playerStatusIndicator;
};

#endif // PLAYERINFORWIDGET_H
