#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {

    mainLayer_ = new QHBoxLayout;
    skinsWindow_ = new SkinsWindow;

    setLayout(mainLayer_);
    mainLayer_->addWidget(skinsWindow_);

    mainLayer_->setContentsMargins(0, 0, 0, 0);
}
MainWindow::~MainWindow() {
    delete skinsWindow_;
    skinsWindow_ = NULL;
    delete mainLayer_;
    mainLayer_ = NULL;
}
