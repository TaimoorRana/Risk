#ifndef STATS_SELECTOR_H
#define STATS_SELECTOR_H
#include <QDialog>
#include <string>

namespace Ui {
class LogSelector;

}
class LogSelector: public QDialog
{
    Q_OBJECT
public:
	explicit LogSelector(QWidget *parent = 0);
	~LogSelector();
	int getSelectedPlayer();
	int getSelectedPhase();

private:
	Ui::LogSelector *ui;
};

#endif // STATS_SELECTOR_H
