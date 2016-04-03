TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    mprimitives.cpp

HEADERS += \
    mprimitives.h \
    inputhandler.hpp

LIBS += -lSDL2


