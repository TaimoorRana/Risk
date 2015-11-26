#ifndef LOG_SELECTOR_H
#define LOG_SELECTOR_H
#include <QDialog>
#include <string>

namespace Ui {
class LogSelector;

}
class LogSelector: public QDialog
{
	Q_OBJECT
public:
	explicit LogSelector(QWidget *parent = 0, int numberOfPlayers=0);
	~LogSelector();
	int getSelectedPlayer();
	std::string getSelectedPhase();
	void setNumberPlayers(int players);
	void generatePlayers(int numberOfPlayers);

private:
	Ui::LogSelector *ui;
	int numberOfPlayers;
};

#endif // STATS_SELECTOR_H
