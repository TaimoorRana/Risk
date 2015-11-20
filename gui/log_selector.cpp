#include "log_selector.h"
#include "ui_log_selector.h"

LogSelector::LogSelector(QWidget *parent): QDialog(parent), ui(new Ui::LogSelector){
	ui->setupUi(this);

}

LogSelector::~LogSelector(){
	delete ui;
}




