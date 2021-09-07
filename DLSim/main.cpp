#include "DLSim.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DLSim mainWindow;
    mainWindow.show();

    return app.exec();
}
