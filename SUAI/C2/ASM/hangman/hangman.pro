TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS = -O0 -masm=intel

SOURCES += main.c

HEADERS += \
    text.h
