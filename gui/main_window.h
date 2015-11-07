#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

#include "risk_map.h"
#include "observer.h"

namespace Ui {
	class MainWindow;
}

enum ToolMode {ADDCOUNTRY, REMCOUNTRY, ADDLINK, REMLINK, OFF};


class MainWindow : public QMainWindow, public Observer {
	Q_OBJECT

public:
	MainWindow(RiskMap* map, QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_filenameLineEdit_textChanged(QString text);
	void on_browsePushButton_clicked();
	void on_loadPushButton_clicked();
	// void on_randOwnerPushButton_clicked();
	// void on_randArmiesPushButton_clicked();
    void on_saveMapPushButton_clicked();
    void on_addCountryPushButton_clicked();
    void on_removeCountryPushButton_clicked();
    void on_addNeighbourPushButton_clicked();
    void on_removeNeighbourPushButton_clicked();


private:
	bool validateFilename(const QString& text);
	void observedUpdated();
	void connectNeighboursVisit(std::map<const std::string, bool>& visited, const Country* country);
    void mousePressEvent(QMouseEvent *event);
    void makePopupWindowAddCountryAppear(int x, int y);
	Ui::MainWindow* ui;
	QGraphicsScene* scene;
	RiskMap* observedMap;
    ToolMode tool;
};


class ClickableMap: public QGraphicsScene{
public:
//    void mousePressEvent(QGraphicsSceneMouseEvent *w);
    ClickableMap();
    ~ClickableMap();
};


#endif // MAINWINDOW_H
