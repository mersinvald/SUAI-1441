TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS=-O0

SOURCES += main.cpp \
    studentid.cpp \
    ID.cpp \
    internationalid.cpp \
    documentmanager.cpp \
    documentfactory.cpp

HEADERS += \
    document.hpp \
    ID.hpp \
    internationalid.hpp \
    studentid.hpp \
    documentmanager.hpp \
    documentfactory.hpp
