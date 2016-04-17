TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    object2D.cpp \
    line.cpp \
    matrix.cpp

HEADERS += \
    inputhandler.hpp \
    primitives.hpp \
    object2D.hpp \
    line.hpp \
    matrix.hpp

LIBS += -lSDL2


