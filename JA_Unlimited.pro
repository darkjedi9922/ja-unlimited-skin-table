#-------------------------------------------------
#
# Project created by QtCreator 2016-07-17T09:40:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JA_Unlimited
TEMPLATE = app


SOURCES += main.cpp\
    MainWindow.cpp \
    SkinsWindow.cpp \
    includes/JGroupBox.cpp \
    includes/JTableView.cpp \
    includes/JAbstractScrollBar.cpp \
    includes/JHScrollBar.cpp \
    includes/JScrollArea.cpp \
    includes/JVScrollBar.cpp \
    includes/JWidget.cpp \
    includes/JBorder.cpp \
    includes/JMargins.cpp \
    includes/JLabel.cpp \
    TeamColorLabel.cpp \

HEADERS  += MainWindow.h \
    SkinsWindow.h \
    includes/JGroupBox.h \
    includes/JTableView.h \
    includes/JAbstractScrollBar.h \
    includes/JHScrollBar.h \
    includes/JScrollArea.h \
    includes/JVScrollBar.h \
    includes/JWidget.h \
    includes/JBorder.h \
    includes/JMargins.h \
    includes/JLabel.h \
    TeamColorLabel.h \

RESOURCES += resources.qrc

RC_ICONS = icon.ico

include(qzip.pri)
