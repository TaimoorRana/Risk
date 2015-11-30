#include <QString>
#include "logscreen.h"
#include "ui_logscreen.h"

LogScreen::LogScreen(GameDriver* driver, std::string logPhase, std::string logPlayer, QWidget *parent): QMainWindow(parent),ui(new Ui::LogScreen) {
	this->driver = driver;

	// Create a new listener (message sink)
	logListener = new LogListener();

	// Decorate it
	if (logPhase == "All phases") {
		logListener = new PhaseLogFilter(logListener, REINFORCEMENT);
		logListener = new PhaseLogFilter(logListener, ATTACK);
		logListener = new PhaseLogFilter(logListener, FORTIFICATION);
	}
	else if (logPhase == "Reinforcement") {
		logListener = new PhaseLogFilter(logListener, REINFORCEMENT);
	}
	else if (logPhase == "Attack") {
		logListener = new PhaseLogFilter(logListener, ATTACK);
	}
	else if (logPhase == "Fortification") {
		logListener = new PhaseLogFilter(logListener, FORTIFICATION);
	}
	if (logPlayer == "All players") {
		for (auto &ent1 : this->driver->getRiskMap()->getPlayers()) {
			std::string playerName = ent1.first;
			logListener = new PlayerLogFilter(logListener, playerName);
		}
	}
	else {
		logListener = new PlayerLogFilter(logListener, logPlayer);
	}

	// Connect it to the logger (message source)
	Logger::getInstance()->attachListener(logListener);

	this->logListener = logListener;
	this->logListener->attachHandler(this);
	ui->setupUi(this);
	ui->textEdit->insertPlainText("Decorated logging started...\n");
}

LogScreen::~LogScreen() {
	this->logListener->detachHandler(this);
	Logger::getInstance()->detachListener(logListener);
	delete logListener;
	delete ui;
}

void LogScreen::messageLogged(std::string message) {
	ui->textEdit->insertPlainText(QString::fromStdString(message));
}
