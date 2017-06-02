INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
CURRENT_DIR = $$PWD

CONFIG += c++11

SOURCES += $$CURRENT_DIR/cmyo.cpp \
    $$CURRENT_DIR/myoform.cpp

HEADERS  += $$CURRENT_DIR/cmyo.h \
    $$CURRENT_DIR/myoform.h

FORMS    +=    $$CURRENT_DIR/myoform.ui
