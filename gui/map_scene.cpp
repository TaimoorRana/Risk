#include <QDebug>
//#include <QString>

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
	CountryQGraphicsObject *item = nullptr;

	switch(parent->getSelectedTool()){
		case ADDCOUNTRY:
            qDebug("MAPSCENE: Add Country Tool had been selected");
            nameDialog.setLastContinentName(lastContinent);
			if(nameDialog.exec() == QDialog::Rejected)
				return;
            lastContinent = nameDialog.getContinentName();
			c = map->addCountry(nameDialog.getCountryName().toStdString(), nameDialog.getContinentName().toStdString(), 0);
			if( c == nullptr)
				return;
			c->setPositionX(xpos);
			c->setPositionY(ypos);
            c->notifyObservers();
			break;
		case REMCOUNTRY:
            qDebug("MAPSCENE: Remove Country Tool had been selected");

            item = getCountryGraphicsObjAt(event);

//            item->getCountry()

			break;
        case MOVCOUNTRY:
            qDebug("MAPSCENE: Move Country Tool had been selected.");
            item = getCountryGraphicsObjAt(event);
            if (item == nullptr) {return;}

            item->setFlag(CountryQGraphicsObject::ItemIsMovable);
            qDebug("Make item movable.");
            break;
		case ADDLINK:
            qDebug("MAPSCENE: Add link between countries.");
            item = getCountryGraphicsObjAt(event);
            if (item == nullptr) {return;}

            if (lastPicked != 0)
            {
				debug("Second pick is " + item->getCountry()->getName());
				map->addNeighbour(item->getCountry()->getName(), lastPicked->getName());
				lastPicked = 0;
            }
            else
            {
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

void MapScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    MainWindow* parent = qobject_cast<MainWindow*>(this->parent());
    int xpos =  event->scenePos().x();
    int ypos =  event->scenePos().y();
    qDebug()<< xpos;
    qDebug()<< ypos;

    CountryQGraphicsObject *countryQ = nullptr;
    countryQ = getCountryGraphicsObjAt(event);
    if (countryQ == nullptr) {return;}

    switch(parent->getSelectedTool())
    {
    case ADDCOUNTRY:
        qDebug("MAPSCENE: ReleaseMouse / Add Country Tool.");

        break;
    case REMCOUNTRY:
        qDebug("MAPSCENE: ReleaseMouse / Rem Country Tool.");
        break;
    case MOVCOUNTRY:
        qDebug("MAPSCENE: ReleaseMouse / Move Country Tool.");
        countryQ->getCountry()->setPositionX(xpos);
        countryQ->getCountry()->setPositionY(ypos);
        countryQ->setFlag(CountryQGraphicsObject::ItemIsMovable,false);
        qDebug("Make item un-movable.");
        break;
    case ADDLINK:
        qDebug("MAPSCENE: ReleaseMouse / Add Link Tool.");
        break;
    case REMLINK:
        qDebug("MAPSCENE: ReleaseMouse / Rem Link Tool.");

        break;
    case OFF:
    default:
        break;
    }

    countryQ->getCountry()->notifyObservers();
}

void MapScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    int xpos =  event->scenePos().x();
    int ypos =  event->scenePos().y();
    qDebug()<< xpos;
    qDebug()<< ypos;

    CountryQGraphicsObject *countryQ = nullptr;
    countryQ = getCountryGraphicsObjAt(event);
    if (countryQ == nullptr) {return;}

    MainWindow* parent = qobject_cast<MainWindow*>(this->parent());
    switch(parent->getSelectedTool())
    {
    case ADDCOUNTRY:
        break;
    case REMCOUNTRY:
        break;
    case MOVCOUNTRY:
        countryQ->getCountry()->setPositionX(xpos);
        countryQ->getCountry()->setPositionY(ypos);
        countryQ->getCountry()->notifyObservers();
        break;
    case ADDLINK:
        break;
    case REMLINK:
        break;
    case OFF:
    default:
        break;
    }
}

CountryQGraphicsObject* MapScene::getCountryGraphicsObjAt(QGraphicsSceneMouseEvent *event){
//    QMutexLocker locker(&mutex);

    QGraphicsItem *itemAt = nullptr;
    CountryQGraphicsObject *item = nullptr;
    itemAt = this->itemAt(event->scenePos(), QTransform());
    item = dynamic_cast<CountryQGraphicsObject*>(itemAt);
    return item;
}
