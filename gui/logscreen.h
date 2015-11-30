#ifndef LOGSCREEN_H
#define LOGSCREEN_H
#include <QMainWindow>
#include <string>
#include "game_driver.h"
#include "logging/logger.h"
#include "logging/log_handler.h"
#include "logging/log_listener.h"
#include "logging/phase_log_filter.h"
#include "logging/player_log_filter.h"

/**
 * The namespace used for linking with .ui file widget.
 */
namespace Ui {
	class LogScreen;
}

/**
 * @brief An implementation of a log handler that displays log messages to the GUI
 */
class LogScreen : public QMainWindow, public LogHandler {
	Q_OBJECT

public:
	explicit LogScreen(GameDriver* driver, std::string logPhase, std::string logPlayer, QWidget *parent=0);
	~LogScreen();

	/**
	 * @brief Observer notification indicating there is a new message to be logged
	 */
	virtual void messageLogged(std::string message);

private:
	Ui::LogScreen *ui;
	LogListener* logListener = nullptr;
	GameDriver* driver = nullptr;
};

#endif // LOGSCREEN_H
