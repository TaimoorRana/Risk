
#include <QDebug>
#include <QString>

#include "map_editor.h"
#include "map_scene.h"
#include "qgraphics_country_item.h"
#include "fortify_dialog.h"
#include "debug.h"
#include "mainscreen.h"

MapScene::MapScene(RiskMap* map, QWidget *parent){
    this->setParent(parent);
    this->map = map;
}

bool MapScene::getEditable() const {
    return this->editable;
}

void MapScene::setEditable(bool editable) {
    this->editable = editable;
}

RiskMap* MapScene::getMap()
{
    return this->map;
}


void MapScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsScene::mousePressEvent(event);
    
    QGraphicsCountryItem *item = nullptr;
    if (!this->editable) {
        MainScreen* parent = qobject_cast<MainScreen*>(this->parent());
        
        switch(parent->getCurrentMode())
        {
            case REINFORCEMENTMODE:
                item = getQGraphicsCountryItemFromEvent(event);
                if (item == nullptr)
                {
                    return;
                }
                
                if(map->getPlayer(item->getCountry()->getPlayer())->getReinforcements() > 0){
                    map->getPlayer(item->getCountry()->getPlayer())->removeReinforcements(1);
                    item->getCountry()->addArmies(1);
                }else{
                    return;
                }
                map->getPlayer(item->getCountry()->getPlayer())->notifyObserver();
                debug(std::to_string(item->getCountry()->getArmies()));
                break;
            case ATTACKMODE:
            case FORTIFICATIONMODE:
                item = getQGraphicsCountryItemFromEvent(event);
                
                if (item == nullptr)
                {
                    return;
                } else
                {
                    if (lastCountryClicked == nullptr)
                    {
                        lastCountryClicked = item->getCountry();
                    }else
                    {
                        std::string firstCountryName = lastCountryClicked->getName();
                        std::string secondCountryName = item->getCountry()->getName();
                        
                        FortifyDialog* fortificationDialog = new FortifyDialog(lastCountryClicked);
                        fortificationDialog->setWindowTitle(QString::fromStdString("Transfering Armies"));
                        
                        // check for adjancency
                        if (map->areCountriesAdjacent(firstCountryName, secondCountryName))
                        {
                            if (lastCountryClicked->getPlayer().compare(item->getCountry()->getPlayer()) == 0)
                            {
                                // pop-up the transfer window
                                fortificationDialog->setOriginCountryName(QString::fromStdString(firstCountryName));
                                fortificationDialog->setDestinationCountryName(QString::fromStdString(secondCountryName));
                            }else
                            {
                                // pop-up the transfer window
                                fortificationDialog->setOriginCountryName(QString::fromStdString("Different"));
                                fortificationDialog->setDestinationCountryName(QString::fromStdString("players"));
                            }
                            
                        } else
                        {
                            // pop-up the transfer window
                            fortificationDialog->setOriginCountryName(QString::fromStdString("Countries not"));
                            fortificationDialog->setDestinationCountryName(QString::fromStdString("adjacent"));
                        }
                        fortificationDialog->show();
                        lastCountryClicked = nullptr;
                    }
                }
                break;
            default:
                break;
        }
        return;
    }
    
    int xpos =  event->scenePos().x();
    int ypos =  event->scenePos().y();
    QRectF r1(xpos-10,ypos-10,20,20);
    QPen p(QColor(13,145,67,255));
    MapEditor* parent = qobject_cast<MapEditor*>(this->parent());
    CountryNameDialog nameDialog(parent);
    Country* c = nullptr;
    
    
    switch(parent->getSelectedTool()){
        case ADDCOUNTRY:
            nameDialog.setLastContinentName(lastContinent);
            if (nameDialog.exec() == QDialog::Rejected) {
                return;
            }
            
            lastContinent = nameDialog.getContinentName();
            c = map->addCountry(Country(nameDialog.getCountryName().toStdString()), nameDialog.getContinentName().toStdString());
            if (c == nullptr) {
                // FIXME inform user of error
                return;
            }
            c->setPositionX(xpos);
            c->setPositionY(ypos);
            this->map->notifyObservers();
            break;
            
        case REMCOUNTRY:
            item = getQGraphicsCountryItemFromEvent(event);
            if (item == nullptr) {
                return;
            }
            map->remCountry(*item->getCountry());
            this->map->notifyObservers();
            break;
            
        case ADDLINK:
            item = getQGraphicsCountryItemFromEvent(event);
            if (item == nullptr) {
                return;
            }
            
            if (lastPicked != nullptr) {
                map->addNeighbour(item->getCountry()->getName(), lastPicked->getName());
                lastPicked = nullptr;
            }
            else {
                lastPicked = item->getCountry();
            }
            break;
            
        case REMLINK:
            qDebug("MAPSCENE: Remove link between countries.");
            item = getQGraphicsCountryItemFromEvent(event);
            if (item == nullptr) {return;}
            
            if (lastPicked != 0)
            {
                debug("Second pick is " + item->getCountry()->getName());
                map->remNeighbour(item->getCountry()->getName(), lastPicked->getName());
                lastPicked = 0;
            }
            else
            {
                debug("First pick is " + item->getCountry()->getName());
                lastPicked = item->getCountry();
            }
        case OFF:
        default:
            break;
    }
}

void MapScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsScene::mouseReleaseEvent(event);
    // Re-draws the whole scene, fixing text that gets left behind from dragging QGraphicsCountryItem objects (due to their out of bound text)
    this->update();
}

QGraphicsCountryItem* MapScene::getQGraphicsCountryItemFromEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem *itemAt = nullptr;
    QGraphicsCountryItem *item = nullptr;
    itemAt = this->itemAt(event->scenePos(), QTransform());
    item = dynamic_cast<QGraphicsCountryItem*>(itemAt);
    return item;
}
