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
#include <QWidget>
#include <QStyle>
#include <QDebug>
#include <QDir>
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include "gameboardview.h"

int main(int argc, char *argv[])
{

    QApplication application(argc, argv);
    MainWindow mw;
    QVBoxLayout *qb = new QVBoxLayout;
    GameBoardView *a = new GameBoardView();
    QGraphicsScene *scene = new QGraphicsScene();
    scene->addWidget((a));
    QGraphicsView *view = new QGraphicsView(scene);
    mw.setCentralWidget(view);
    /* QVBoxLayout *mainLayout = new  QVBoxLayout;
    mainLayout->setSpacing(10);
    QGraphicsScene * scene = new QGraphicsScene();
    QGraphicsView * view = new QGraphicsView(scene);

    // mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    QLabel *playersHeader = new QLabel();
    playersHeader->setText("Select number of players");

    QComboBox * comboBox= new QComboBox();
    comboBox->addItem(("1"));
    comboBox->addItem(("2"));
    comboBox->addItem(("3"));
    comboBox->addItem(("4"));
    //comboBox->setAutoCompletion(true);
    //comboBox->setEnabled(true);
    //comboBox->setMaximumWidth(150);
    playersHeader->setBuddy(comboBox);
    mainLayout->addWidget(playersHeader);
    mainLayout->addWidget(comboBox);*/
    // playersHeader->setMargin(1);
    //playersHeader->setBuddy(comboBox);
    //stylesheet
    //QFile stylesheet("styleSheet.qss");
    //stylesheet.open(QFile::ReadOnly);
    // const QString setSheet = QLatin1String(stylesheet.readAll());
    //application.setStyleSheet(setSheet);
    // create an item to put into the scene
    /* Rect * rect = new Rect();
    rect->setRect(40,0,100,100);
    // make rect focusable
    rect->setFlag(QGraphicsItem::ItemIsFocusable);
    rect->setFocus();
    scene->addWidget((comboBox));
    scene->addItem(rect);

    // add the item to the scene*/
    QPushButton *startGame = new QPushButton("start Game");
    //mainLayout->addWidget(startGame);
    //scene->addWidget((comboBox));
    //scene->addWidget(playersHeader);


    //menu bar
    QMenuBar *menuBar = new QMenuBar(0);
    menuBar->addAction("Save");
    menuBar->addSeparator();
    menuBar->addAction("Load");
    //view->setLayout(mainLayout);
    // menuBar->setVisible(true);
    // mainLayout->addWidget(menuBar);
    //menuBar->CornerWidget(Qt::TopLeftCorner);

    //menuBar->isTopLevel();
    // menuBar->setCornerWidget();
    //menuBar->setStyleSheet(setSheet);
    //scene->addWidget(menuBar);
    // view->scale(2,2);   //zoom in
    //view->scale(.5,.5); //zoom out


    qDebug() << "App path : " << QDir::currentPath();

    mw.show();

    return application.exec();
}

