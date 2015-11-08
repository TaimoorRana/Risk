#include <QDebug>
#include "main_window.h"

#include "map_scene.h"
#include "enum_tooltype.h"
#include "country_qgraphics_object.h"

MapScene::MapScene(RiskMap* map, QWidget *parent){
	this->setParent(parent);
	this->map = map;
}

void MapScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
	QGraphicsScene::mousePressEvent(event);

	int xpos =  event->scenePos().x();
	int ypos =  event->scenePos().y();
	qDebug()<< xpos;
	qDebug()<< ypos;
	QRectF r1(xpos-10,ypos-10,20,20);
	QPen p(QColor(13,145,67,255));
	MainWindow* parent = qobject_cast<MainWindow*>(this->parent());
	CountryNameDialog nameDialog(parent);
	Country* c;
	CountryQGraphicsObject *item;

	switch(parent->getSelectedTool()){
		case ADDCOUNTRY:
			qDebug("Add Country Tool had been selected");
			if(nameDialog.exec() == QDialog::Rejected)
				return;
//			this->addEllipse(r1,p,QBrush());


			c = map->addCountry(nameDialog.getCountryName().toStdString(), nameDialog.getContinentName().toStdString(), 0);
			if( c == nullptr)
				return;

			c->setPositionX(xpos);
			c->setPositionY(ypos);

			item = new CountryQGraphicsObject(c);
			item->setPos(event->scenePos());
			this->addItem(item);

			break;
		case REMCOUNTRY:
			qDebug("Remove Country Tool had been selected");
			break;
		case ADDLINK:
			qDebug("Add link between countries.");

			break;
		case REMLINK:
		case OFF:
		default:
			return;
	}
}
