#include "cards_trade_dialog.h"
#include "ui_cards_trade_dialog.h"
#include "librisk.h"

/**
 * @brief Pop-up dialog to set the number of cards the user wants to trade
 */
CardsTradeDialog::CardsTradeDialog(GameDriver* driver, QWidget *parent) :QDialog(parent), ui(new Ui::CardsTradeDialog)
{
	ui->setupUi(this);
	this->driver = driver;
	ui->cardsSlider->setMaximum(driver->getRiskMap()->getPlayer(driver->getCurrentPlayerName())->getCards());
	ui->cardsSlider->setMinimum(2);
}

CardsTradeDialog::~CardsTradeDialog()
{
	delete ui;
}

void CardsTradeDialog::on_cardsSlider_valueChanged(int value)
{
	numCardsSelected = value;
	armiesEarned = convertCardsToReinforcements(numCardsSelected);
	ui->numArmiesEarned->setText(QString::fromStdString("Armies received: " + std::to_string(armiesEarned)));
}

/**
 * @brief Slot implementation start the fortification action.
 */
void CardsTradeDialog::accept()
{
	// add the reinforcements to the player
	this->driver->addCardsTradeReinforcements(armiesEarned);

	// deduct the amount of traded cards from the players deck
	this->driver->updatePlayerCards(-numCardsSelected);

	this->close();
	this->setResult(QDialog::Accepted);
}
