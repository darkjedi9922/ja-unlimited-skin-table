#include "MainWindow.h"
#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    QSplashScreen splashScreen(QPixmap(":resources/splash.jpg"));
    splashScreen.show();

    MainWindow *mainWindow = new MainWindow;
    mainWindow->setMinimumHeight(200);

    splashScreen.finish(mainWindow);

    mainWindow->showMaximized();

    return application.exec();
}
