#ifndef LOG_SELECTOR_H
#define LOG_SELECTOR_H
#include <QDialog>
#include <string>

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
	explicit LogSelector(QWidget *parent = 0, int numberOfPlayers=0);
	~LogSelector();
	/**
	 * @brief getSelectedPlayer
	 * @return
	 */
	int getSelectedPlayer();
	/**
	 * @brief getSelectedPhase
	 * @return
	 */
	std::string getSelectedPhase();
	/**
	 * @brief setNumberPlayers
	 * @param players
	 */
	void setNumberPlayers(int players);
	/**
	 * @brief generatePlayers
	 * @param numberOfPlayers
	 */
	void generatePlayers(int numberOfPlayers);

private:
	Ui::LogSelector *ui;
	int numberOfPlayers;
};

#endif // STATS_SELECTOR_H
