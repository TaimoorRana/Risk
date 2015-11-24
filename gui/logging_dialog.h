#ifndef LOGGING_DIALOG_H
#define LOGGING_DIALOG_H

#include <QDialog>

class Player;

namespace Ui {
	class LoggingDialog;
}

class LoggingDialog : public QDialog
{
	Q_OBJECT

public:
	explicit LoggingDialog(const std::map<std::string, Player> &players, QWidget *parent = 0);
	~LoggingDialog();
	void addObservableItemPlayer(QString label);
	void addObservableItemPhase(QString label);
	void populatePlayers();
private:
	Ui::LoggingDialog *ui;
};

#endif // LOGGING_DIALOG_H
