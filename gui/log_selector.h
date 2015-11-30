#ifndef LOG_SELECTOR_H
#define LOG_SELECTOR_H
#include <QDialog>
#include <string>
#include <vector>

namespace Ui {
	class LogSelector;
}
/**
 * @brief The LogSelector class allows you to select how many players
 * and which phases to log
 */
class LogSelector: public QDialog
{
	Q_OBJECT
public:
	/**
	 * @brief LogSelector
	 * @param parent the mainwindow
	 * @param numberOfPlayers gets the number of players in the game and provides this as an option
	 */
	explicit LogSelector(std::vector<std::string> playerNames, QWidget *parent = 0);
	~LogSelector();

	/**
	 * @brief getSelectedPlayer
	 * @return
	 */
	std::string getSelectedPlayer();

	/**
	 * @brief getSelectedPhase
	 * @return
	 */
	std::string getSelectedPhase();

private:
	Ui::LogSelector *ui;
};

#endif // STATS_SELECTOR_H
