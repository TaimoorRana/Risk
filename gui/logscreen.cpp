#include <QString>
#include "logscreen.h"
#include "ui_logscreen.h"

LogScreen::LogScreen(GameDriver* driver, std::string logPhase, std::string logPlayer, QWidget *parent): QMainWindow(parent),ui(new Ui::LogScreen) {
	this->driver = driver;

	// Create a new listener (message sink)
	this->logListener = new LogListener();

	// Decorate it
	if (logPhase == "All phases") {
		this->logListener = new PhaseLogFilter(this->logListener, REINFORCEMENT);
		this->logListener = new PhaseLogFilter(this->logListener, ATTACK);
		this->logListener = new PhaseLogFilter(this->logListener, FORTIFICATION);
	}
	else if (logPhase == "Reinforcement") {
		this->logListener = new PhaseLogFilter(this->logListener, REINFORCEMENT);
	}
	else if (logPhase == "Attack") {
		this->logListener = new PhaseLogFilter(this->logListener, ATTACK);
	}
	else if (logPhase == "Fortification") {
		this->logListener = new PhaseLogFilter(this->logListener, FORTIFICATION);
	}
	if (logPlayer == "All players") {
		for (auto &ent1 : this->driver->getRiskMap()->getPlayers()) {
			std::string playerName = ent1.first;
			this->logListener = new PlayerLogFilter(this->logListener, playerName);
		}
	}
	else {
		this->logListener = new PlayerLogFilter(this->logListener, logPlayer);
	}

	// Connect it to the logger (message source)
	Logger::getInstance()->attachListener(this->logListener);

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
