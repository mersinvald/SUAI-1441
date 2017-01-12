TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS+=-fopenmp -Ofast

QMAKE_CXXFLAGS+=-fprofile-generate
QMAKE_LFLAGS+=-fprofile-generate
#QMAKE_CXXFLAGS+=-fprofile-use
#QMAKE_LFLAGS+=-fprofile-use

LIBS+=-lgomp -lpthread

SOURCES += \
    matrix.cpp \
    matrix2.cpp \
    matrix3.cpp \
    task5.1.cpp \
    matrix4.cpp

HEADERS += \
    matrix.hpp \
    matrix2.hpp \
    matrix3.hpp \
    matrix4.hpp
