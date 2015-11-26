#ifndef LOGSCREEN_H
#define LOGSCREEN_H
#include <QMainWindow>
#include <string>
#include "observer.h"
#include "game_modes.h"
#include "component.h"

namespace Ui{
class LogScreen;
}

class LogScreen : public QMainWindow, public Observer

{
	Q_OBJECT

public:
	explicit LogScreen(QWidget *parent=0);
	~LogScreen();
	void setPlayers(int nPlayers);
	void setState(std::string stateSelected);
	int getPlayers();
	void setCurrentMode ( Mode mode);
	Mode getCurrentMode();
	std::string getState();
	void update();
	virtual void observedUpdated();
private:
	Ui::LogScreen *ui=nullptr;
	int players=55;
	std::string states;
	Mode currentMode;
	Component *component = nullptr;

};

#endif // LOGSCREEN_H
