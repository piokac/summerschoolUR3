INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
CURRENT_DIR = $$PWD

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    cgamepad.cpp

HEADERS  += mainwindow.h \
    cgamepad.h

FORMS    +=    mainwindow.ui
