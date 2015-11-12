#ifndef MAINSCREEN_H
#define MAINSCREEN_H
#include <QMainWindow>
#include <QMouseEvent>
#include <QString>

#include <playernamedialog.h>
#include <risk_map.h>
#include "map_editor.h"
#include "ui_mainscreen.h"

#include "game_modes.h"


namespace Ui {
	class MainScreen;
}

class MainScreen : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	explicit MainScreen(RiskMap* map, QWidget *parent = 0);
	~MainScreen();
	void addPlayerView(QWidget* pvWidget);
	bool setupPlayers();
	void observedUpdated();

	/**
	 * @brief getCurrentMode
	 * @return The current game mode (REINFORCEMENTMODE, ATTACKMODE, FORTIFICATIONMODE)
	 */
	Mode getCurrentMode();
	void setCurrentMode(Mode newMode);

	/**
	 * @brief endPhase This function simulates the click of the end phase button and switches to next player's turn
	 */
	void endPhase();

	void setCurrentPlayer(std::string name);
	std::string getCurrentPlayer();

private slots:
	void on_mapEditorAction_triggered();
	void on_pushButton_clicked();


private:
	std::string playerName = "";
	std::string mapPath = "";
	int CPUs = 0;
	Ui::MainScreen *ui = nullptr;
	MapEditor *editor = nullptr;
	RiskMap *map = nullptr;
	MapScene *scene = nullptr;
	Mode currentMode;
	std::string currentPLayerName;
};

#endif // MAINSCREEN_H
