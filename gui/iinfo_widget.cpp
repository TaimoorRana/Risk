#include "iinfo_widget.h"

void IInfoWidget::draw()
{
	QColor playerColor = this->scene->getPlayerColor(this->player->getName());
	std::string hexColor = playerColor.name().toStdString();
	QLabel *colorLabel = new QLabel();
	colorLabel->setStyleSheet(QString::fromStdString("QLabel { background-color : " + hexColor + "; }"));
	mainLayout->addLayout(subMainLayout);
	subMainLayout->addWidget(colorLabel);
	subMainLayout->addLayout(nameLayout);
	subMainLayout->addLayout(valueLayout);
	subMainLayout->addItem(spacer);
	std::vector<IAttribute*>::iterator it;
	for(it = attributes.begin(); it != attributes.end(); it++)
	{
		nameLayout->addWidget((*it)->getName());
		valueLayout->addWidget((*it)->getValue());
	}
	this->setLayout(mainLayout);
}
