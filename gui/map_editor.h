#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <QMainWindow>
#include "country_name_dialog.h"
#include "enum_tooltype.h"
#include "map_scene.h"
#include "observer.h"
#include "risk_map.h"
#include "ui_map_editor.h"
#include "enum_savetype.h"

namespace Ui {
	class MapEditor;
}


class MapEditor : public QMainWindow, public Observer {
	Q_OBJECT
public:
	MapEditor(QWidget *parent = 0);
	~MapEditor();
	ToolMode getSelectedTool();
	void observedUpdated();
	bool hasEnding(std::string const &fullString, std::string const &ending);

private slots:
	void on_filenameLineEdit_textChanged(QString text);
	void on_browsePushButton_clicked();
	void on_loadPushButton_clicked();
	void on_clearMapPushButton_clicked();

	void on_saveMapPushButton_clicked();
	void on_addCountryPushButton_clicked();
	void on_removeCountryPushButton_clicked();
	void on_addNeighbourPushButton_clicked();
	void on_removeNeighbourPushButton_clicked();


private:
	std::string mapPath = "";
	Ui::MapEditor* ui = nullptr;
	MapScene* scene = nullptr;
	RiskMap* observedMap = nullptr;
	GameDriver* dummyDriver = nullptr;
	ToolMode tool = OFF;
	SaveType saveMode = MAP;

	bool validateFilename(const QString& text);
	void resetToolbar();
};
#endif // MAPEDITOR_H
