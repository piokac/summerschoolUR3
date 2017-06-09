INCLUDEPATH += $$PWD
#DEPENDPATH += $$PWD
CURRENT_DIR = $$PWD
CONFIG += c++11
SOURCES += $$CURRENT_DIR/ckalibracja.cpp \
$$CURRENT_DIR/ckalibracja1d.cpp \
$$CURRENT_DIR/ckalibracja2d.cpp \
$$CURRENT_DIR/ckalibracja3d.cpp \
$$CURRENT_DIR/mainwindow.cpp \
$$CURRENT_DIR/main.cpp
HEADERS += $$CURRENT_DIR/kalibracja.h \
$$CURRENT_DIR/kalibracja1d.h \
$$CURRENT_DIR/kalibracja2d.h \
$$CURRENT_DIR/kalibracja3d.h \
$$CURRENT_DIR/main.h
FORMS += $$CURRENT_DIR/mainwindow.ui
