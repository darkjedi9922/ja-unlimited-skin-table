#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include "SkinsWindow.h"

class MainWindow : public QWidget
{
public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

private:
    QHBoxLayout *mainLayer_;
    SkinsWindow *skinsWindow_;
};

#endif // MAINWINDOW_H
