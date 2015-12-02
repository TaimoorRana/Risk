#include "cards_trade_dialog.h"
#include "ui_cards_trade_dialog.h"

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

void CardsTradeDialog::on_cardsSlider_sliderMoved(int value)
{
    numCardsSelected = value;

    switch (value)
    {
    case 2:
        armiesEarned = 2;
        break;
    case 3:
        armiesEarned = 4;
        break;
    case 4:
        armiesEarned = 7;
        break;
    case 5:
        armiesEarned = 10;
        break;
    case 6:
        armiesEarned = 13;
        break;
    case 7:
        armiesEarned = 17;
        break;
    case 8:
        armiesEarned = 21;
        break;
    case 9:
        armiesEarned = 25;
        break;
    case 10:
        armiesEarned = 30;
        break;
    }

    ui->numArmiesEarned->setText(QString::fromStdString("Armies received: "+std::to_string(armiesEarned)));
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
	// TODO: error validation
}
