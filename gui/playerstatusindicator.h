#ifndef PLAYERSTATUSINDICATOR_H
#define PLAYERSTATUSINDICATOR_H

#include <QWidget>

namespace Ui {
class PlayerStatusIndicator;
}

class PlayerStatusIndicator : public QWidget
{
	Q_OBJECT

public:
	explicit PlayerStatusIndicator(std::string baseColor, QWidget *parent = 0);
	~PlayerStatusIndicator();
	void turnOn();
	void turnOff();
private:
	Ui::PlayerStatusIndicator *ui;
	std::string baseColor;
	const std::string indicatorColor = "#ffffff"; //white
};

#endif // PLAYERSTATUSINDICATOR_H
