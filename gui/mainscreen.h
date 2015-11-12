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
	void setCPUs(int total);
	void setPlayerName(std::string name);
	bool setupPlayers();
	void observedUpdated();
	Mode getCurrentMode();
    void setCurrentMode(Mode newMode);
    void endPhase();
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

	void setupPlayer();
	void setupCPUs();
};

#endif // MAINSCREEN_H
