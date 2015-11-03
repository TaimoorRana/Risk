#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

#include "map.h"
#include "observer.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow, public Observer {
	Q_OBJECT

public:
	MainWindow(Map* map, QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_filenameLineEdit_textChanged(QString text);
	void on_browsePushButton_clicked();
	void on_loadPushButton_clicked();

private:
	bool validateFilename(const QString& text);
	void observedUpdated();
	void connectNeighboursVisit(std::map<const Country*, bool>& visited, Country* country);
	Ui::MainWindow* ui;
	QGraphicsScene* scene;
	Map* observedMap;
};

#endif // MAINWINDOW_H
