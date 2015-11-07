#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QMainWindow>
#include <playernamedialog.h>
#include <risk_map.h>

namespace Ui {
class MainScreen;
}

class MainScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScreen(RiskMap* map,QWidget *parent = 0);
    ~MainScreen();
    void mousePressEvent(QMouseEvent *e);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainScreen *ui;
    PlayerNameDialog *nameDialog;
    RiskMap *map;
    void setupPlayers();
};

#endif // MAINSCREEN_H
