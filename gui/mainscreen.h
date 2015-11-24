#ifndef MAINSCREEN_H
#define MAINSCREEN_H
#include <QMainWindow>
#include <QMouseEvent>
#include <QString>

#include "game_modes.h"
#include "map_editor.h"
#include "playernamedialog.h"
#include "risk_map.h"
#include "ui_mainscreen.h"

namespace Ui {
	class MainScreen;
}

class MainScreen : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	explicit MainScreen(RiskMap* map, QWidget *parent = 0);
	~MainScreen();
	bool setupPlayers();
	void observedUpdated();

	/**
	 * @brief endPhase This function simulates the click of the end phase button and switches to next player's turn
	 */
	void endPhase();
	void setReinforcements();
	void nextTurn();
	std::vector<int> getVectorOfIndicesRandomCountryAccess(int nCountries);

private slots:
	/**
	 * @brief Callback to handle user selecting File > Load.
	 */
	void on_loadAction_triggered();

	/**
	 * @brief Callback to handle user selecting File > Save.
	 */
	void on_saveAction_triggered();

	/**
	 * @brief Callback to handle user selecting File > Map Editor.
	 */
	void on_mapEditorAction_triggered();

	/**
	 * @brief Callback to end the current phase, or advance to the next turn.
	 */
	void on_endPhasePushButton_clicked();

	void on_loggingOptionsPushButton_clicked();

private:
	std::string playerName = "";
	std::string mapPath = "";
	Ui::MainScreen *ui = nullptr;
	MapEditor *editor = nullptr;
	RiskMap *map = nullptr;
	MapScene *scene = nullptr;
	void initializeMode();
	Player* playerRoundRobin(int i);
};

#endif // MAINSCREEN_H
