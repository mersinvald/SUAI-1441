TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    string.cpp \
    init.cpp

HEADERS += \
    string.hpp \
    sharedptr.hpp \
    log.hpp
