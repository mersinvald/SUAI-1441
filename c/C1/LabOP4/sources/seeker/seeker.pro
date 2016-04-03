TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += std99
SOURCES += main.c

include(deployment.pri)
qtcAddDeployment()

