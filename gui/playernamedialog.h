#ifndef PLAYERNAMEDIALOG_H
#define PLAYERNAMEDIALOG_H

#include <QDialog>
#include <string>

namespace Ui {
class PlayerNameDialog;
}

class PlayerNameDialog : public QDialog
{
	Q_OBJECT
public:
	explicit PlayerNameDialog(QWidget *parent = 0);
	~PlayerNameDialog();
	std::string getMapPath();
	int getPlayerCount();

private slots:
	void on_mapPathBrowsePushButton_clicked();

private:
	Ui::PlayerNameDialog *ui;
};

#endif // PLAYERNAMEDIALOG_H
