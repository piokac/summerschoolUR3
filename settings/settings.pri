INCLUDEPATH += $$PWD
#DEPENDPATH += $$PWD
CURRENT_DIR = $$PWD

CONFIG += c++11

SOURCES +=$$CURRENT_DIR/settings.cpp \
$$CURRENT_DIR/settingswindow.cpp

HEADERS +=$$CURRENT_DIR/settings.h \
$$CURRENT_DIR/settingswindow.h

FORMS += $$CURRENT_DIR/settingswindow.ui
