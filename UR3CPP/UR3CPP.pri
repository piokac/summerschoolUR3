INCLUDEPATH += $$PWD
#DEPENDPATH += $$PWD
CURRENT_DIR = $$PWD

CONFIG += c++11

SOURCES +=	$$CURRENT_DIR/UR3Intermediator.cpp \
$$CURRENT_DIR/UR3Message.cpp \
$$CURRENT_DIR/UR3MessageOut.cpp

HEADERS +=	$$CURRENT_DIR/UR3Intermediator.h \
$$CURRENT_DIR/UR3Message.h \
$$CURRENT_DIR/UR3MessageOut.h
