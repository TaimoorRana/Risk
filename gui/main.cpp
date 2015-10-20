#include <QApplication>
#include "risk.h"
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QMenuBar>
#include <QComboBox>
#include <QFile>
#include <QLabel>
#include "new.h"
#include "rect.h"
#include <QWidget>
#include <QStyle>
#include <QDebug>
#include <QDir>

int main(int argc, char *argv[])
{

    QApplication application(argc, argv);
    MainWindow mw;
    QLabel *playersHeader = new QLabel("number of players");
    QGraphicsScene * scene = new QGraphicsScene();
    QComboBox * comboBox= new QComboBox();
    comboBox->addItem(("1"));
    comboBox->addItem(("2"));
    comboBox->addItem(("3"));
    comboBox->addItem(("4"));
    comboBox->setAutoCompletion(true);
    comboBox->setEnabled(true);
   // playersHeader->setMargin(1);
    playersHeader->setBuddy(comboBox);
    //stylesheet
    QFile stylesheet("styleSheet.qss");
    stylesheet.open(QFile::ReadOnly);
    const QString setSheet = QLatin1String(stylesheet.readAll());
    comboBox->setStyleSheet(setSheet);
    // create an item to put into the scene
    Rect * rect = new Rect();
    rect->setRect(40,0,100,100);
    // make rect focusable
    rect->setFlag(QGraphicsItem::ItemIsFocusable);
    rect->setFocus();
    scene->addWidget((comboBox));
    scene->addItem(rect);
    scene->addWidget(playersHeader);
    // add the item to the scene
    QGraphicsView * view = new QGraphicsView(scene);
    //menu bar
    QMenuBar *menuBar = new QMenuBar(0);
    menuBar->addAction("Save");
    menuBar->addSeparator();
    menuBar->addAction("Load");
    menuBar->setVisible(true);

    //menuBar->isTopLevel();
    // menuBar->setCornerWidget();
    menuBar->setStyleSheet(setSheet);
    scene->addWidget(menuBar);
    view->scale(2,2);   //zoom in
    view->scale(.5,.5); //zoom out
    mw.setCentralWidget(view);

    qDebug() << "App path : " << QDir::currentPath();

    mw.show();

    return application.exec();
}

