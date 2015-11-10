#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QMainWindow>
#include <playernamedialog.h>
#include <risk_map.h>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>
#include <QLabel>
#include "ui_mainscreen.h"
#include "player.h"
#include "player_view.h"
#include "playerinfowidget.h"

namespace Ui {
class MainScreen;
}

class MainScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScreen(RiskMap* map,QWidget *parent = 0);
    ~MainScreen();
    void mousePressEvent(QMouseEvent *e);
    void addPlayerView(QWidget* pvWidget);
	void setCPUs(int total);
	void setPLayerName(QString name);
	void setupPlayers();

private slots:
    void on_pushButton_clicked();

private:
	QString playerName;
	int CPUs;
    Ui::MainScreen *ui;
    PlayerNameDialog *nameDialog;
    RiskMap *map;

	void setupPlayer();
	void setupCPUs();
};

#endif // MAINSCREEN_H
