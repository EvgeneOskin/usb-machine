include(../defaults.pri)

TEMPLATE = app
CONFIG += qt warn_on opengl
QT += widgets core opengl

CONFIG += testcase
QT += testlib

CONFIG   -= app_bundle

SOURCES += main.cpp \
    testoptions.cpp

HEADERS += \
    testoptions.h

#QMAKE_CXXFLAGS_RELEASE += -O3

LIBS += -L../lib -lusb_machine



