#ifndef PLAYERINFOWIDGET_H
#define PLAYERINFOWIDGET_H

#include <QWidget>
#include "player_view.h"

namespace Ui {
class PlayerInfoWidget;
}

class PlayerInfoWidget : public QWidget
{
	Q_OBJECT

public:
	explicit PlayerInfoWidget(QWidget *parent = 0, PlayerView* pv = 0);
	~PlayerInfoWidget();
	void setPlayerInfo();

private:
	Ui::PlayerInfoWidget *ui;
	PlayerView* pv;
};

#endif // PLAYERINFORWIDGET_H
