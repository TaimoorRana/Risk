#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "risk_map.h"
#include "observer.h"
#include "country_name_dialog.h"
#include "enum_tooltype.h"
#include "map_scene.h"

namespace Ui {
	class MainWindow;
}



class MainWindow : public QMainWindow, public Observer {
	Q_OBJECT

public:
	MainWindow(RiskMap* map, QWidget *parent = 0);
	~MainWindow();
    ToolMode getSelectedTool();

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
	Ui::MainWindow* ui;
    MapScene* scene;
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
