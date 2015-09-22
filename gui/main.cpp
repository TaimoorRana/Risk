#include <QApplication>
#include "risk.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    MainWindow mw;
    mw.show();

    return application.exec();
}
