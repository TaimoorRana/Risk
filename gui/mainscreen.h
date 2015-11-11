#ifndef MAINSCREEN_H
#define MAINSCREEN_H
#include <QMainWindow>
#include <QMouseEvent>
#include <QString>

#include <playernamedialog.h>
#include <risk_map.h>
#include "map_editor.h"
#include "ui_mainscreen.h"

namespace Ui {
    class MainScreen;
}

class MainScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScreen(RiskMap* map, QWidget *parent = 0);
    ~MainScreen();
    void mousePressEvent(QMouseEvent *e);
    void addPlayerView(QWidget* pvWidget);
	void setCPUs(int total);
	void setPLayerName(QString name);
	void setupPlayers();

private slots:
    void on_pushButton_clicked();
    void on_mapEditorAction_triggered();

private:
	QString playerName;
	int CPUs;
    Ui::MainScreen *ui=0;
    PlayerNameDialog *nameDialog;
    MapEditor *editor=0;
    RiskMap *map=0;

	void setupPlayer();
	void setupCPUs();
};

#endif // MAINSCREEN_H
