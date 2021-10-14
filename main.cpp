#include "GrimoireCalculator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GrimoireCalculator w;
    QPixmap pixmap;
    pixmap.load("icon.ico");
    w.setWindowIcon(pixmap);
    w.show();
    return a.exec();
}
