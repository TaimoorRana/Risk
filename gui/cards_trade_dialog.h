#ifndef CARDS_TRADE_DIALOG_H
#define CARDS_TRADE_DIALOG_H

#include <QDialog>
#include <QString>
#include "game_driver.h"

namespace Ui {
class CardsTradeDialog;
}

class CardsTradeDialog : public QDialog
{
	Q_OBJECT

public:
		explicit CardsTradeDialog(GameDriver* driver, QWidget *parent = 0);
		~CardsTradeDialog();
	void accept();
private slots:
		void on_cardsSlider_valueChanged(int value);
private:
		Ui::CardsTradeDialog *ui;
		GameDriver* driver = nullptr;
		int armiesEarned = 0;
		int numCardsSelected = 0;
};

#endif // CARDS_TRADE_DIALOG_H
