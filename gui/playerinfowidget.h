#ifndef PLAYERINFOWIDGET_H
#define PLAYERINFOWIDGET_H

#include <QWidget>
#include "map_scene.h"
#include "game_driver.h"
#include "player.h"

namespace Ui {
class PlayerInfoWidget;
}

class PlayerInfoWidget : public QWidget, public Observer
{
	Q_OBJECT

public:
	explicit PlayerInfoWidget(GameDriver* driver, Player* subject, QColor color, QWidget *parent = 0);
	~PlayerInfoWidget();
	void observedUpdated();

private:
	Ui::PlayerInfoWidget *ui;
	GameDriver* driver = nullptr;
	Player* player = nullptr;
	QColor playerColor;
};

#endif // PLAYERINFORWIDGET_H
