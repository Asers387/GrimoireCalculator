#include "GrimoireCalculator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("./images/icon.ico"));
    GrimoireCalculator w;
    w.show();
    return a.exec();
}
