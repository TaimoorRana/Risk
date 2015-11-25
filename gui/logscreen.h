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
	void setPlayers(int nPlayes);
	void setState(std::string state);
private:
	Ui::LogScreen *ui=nullptr;
	int players;

};

#endif // LOGSCREEN_H
