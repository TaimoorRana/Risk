#ifndef LOGSCREEN_H
#define LOGSCREEN_H
#include <QMainWindow>
#include <string>


namespace Ui{
class LogScreen;
}

class LogScreen : public QMainWindow

{
	Q_OBJECT

public:
	explicit LogScreen(QWidget *parent=0);
	~LogScreen();
	void setPlayers(int nPlayers);
	void setState(std::string stateSelected);
	int getPlayers();
	std::string getState();
	void update();
private:
	Ui::LogScreen *ui=nullptr;
	int players=55;
	std::string states;

};

#endif // LOGSCREEN_H
