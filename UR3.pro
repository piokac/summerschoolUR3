#-------------------------------------------------
#
# Project created by QtCreator 2017-05-19T13:13:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include (./UR3CPP/UR3CPP.pri)
include (./settings/settings.pri)
#braki plików pri: kalibracja, settings, gamepadUr3, controlpanel
include (./MYO/MYO.pri)
# niepoprawny include (./GamepadUr3/GamepadUr3.pri)
TARGET = UR3
TEMPLATE = app


SOURCES += main.cpp\
        ur3mainwindow.cpp \
    main.cpp

HEADERS  += ur3mainwindow.h

FORMS    += ur3mainwindow.ui
