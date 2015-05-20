include(../defaults.pri)

TEMPLATE = app
TARGET = usb_machine
CONFIG            += qt warn_on opengl
QT                += widgets core opengl

SOURCES = main.cpp

target.path = ./usb_machine
INSTALLS += target

#QMAKE_CXXFLAGS_RELEASE += -O3

LIBS += -L../lib -lusb_machine

