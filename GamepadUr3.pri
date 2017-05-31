INCLUDEPATH += $$PWD
#DEPENDPATH += $$PWD
CURRENT_DIR = $$PWD

CONFIG += c++11

SOURCES +=	$$CURRENT_DIR/nazwa_pliku1.cpp 
$$CURRENT_DIR/nazwa_pliku2.cpp 
$$CURRENT_DIR/nazwa_pliku3.cpp

HEADERS +=	$$CURRENT_DIR/nazwa_pliku1.h 
$$CURRENT_DIR//nazwa_pliku2.h 
$$CURRENT_DIR//nazwa_pliku3.h
FORMS += $$CURRENT_DIR/nazwa_formularza1.ui 
$$CURRENT_DIR/nazwa_formularza2.ui