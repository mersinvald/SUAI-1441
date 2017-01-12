TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS=-O0

SOURCES += main.cpp \
    ID.cpp \
    AbstractDocument.cpp \
    DocumentFactory.cpp \
    DocumentManager.cpp \
    InternationalID.cpp \
    StudentID.cpp

HEADERS += \
    ID.hpp \
    AbstractDocument.hpp \
    DocumentFactory.hpp \
    DocumentManager.hpp \
    InternationalID.hpp \
    StudentID.hpp
