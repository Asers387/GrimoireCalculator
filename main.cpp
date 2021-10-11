#include "GrimoireCalculator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GrimoireCalculator w;
    w.show();
    return a.exec();
}
