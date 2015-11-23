#ifndef LOGSCREEN_H
#define LOGSCREEN_H
#include <QMainWindow>


namespace Ui{
class LogScreen;
}

class LogScreen : public QMainWindow

{
	Q_OBJECT

public:
	explicit LogScreen(QWidget *parent=0);
	~LogScreen();
private:
	Ui::LogScreen *ui=nullptr;
};

#endif // LOGSCREEN_H
