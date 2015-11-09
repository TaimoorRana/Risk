#include <QDebug>
#include "main_window.h"

#include "map_scene.h"
#include "enum_tooltype.h"
#include "country_qgraphics_object.h"
#include "debug.h"

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
	QGraphicsItem *itemAt = nullptr;
	CountryQGraphicsObject *item = nullptr;

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
			break;
		case REMCOUNTRY:
			qDebug("Remove Country Tool had been selected");

//			qobject_cast<CountryQGraphicsObject*>

//			qDebug()<< typeid(dynamic_cast<CountryQGraphicsObject*>(this->itemAt(event->scenePos(), QTransform()))).name();
//			if ( (dynamic_cast<CountryQGraphicsObject*>(this->itemAt(event->scenePos(), QTransform()))->getCountry()) == nullptr)
//				qDebug("Null pointer");

//			qDebug()<< (dynamic_cast<CountryQGraphicsObject*>(this->itemAt(event->scenePos(), QTransform()))->getCountry());
//			item = dynamic_cast<CountryQGraphicsObject*>(this->itemAt(event->scenePos(), QTransform()));
//			map->remCountry(item->getCountry());
//			delete item;

			break;
		case ADDLINK:
			qDebug("Add link between countries.");
			itemAt = this->itemAt(event->scenePos(), QTransform());
			item = dynamic_cast<CountryQGraphicsObject*>(itemAt);
			if (item == nullptr) {
				return;
			}
			if (lastPicked != 0) {
				debug("Second pick is " + item->getCountry()->getName());
				map->addNeighbour(item->getCountry()->getName(), lastPicked->getName());
				lastPicked = 0;
			}else{
				debug("First pick is " + item->getCountry()->getName());
				lastPicked = item->getCountry();
			}
			break;
		case REMLINK:
		case OFF:
		default:
			return;
	}
}
