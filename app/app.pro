include(../defaults.pri)

TEMPLATE = app
TARGET = usb_machine
CONFIG            += qt warn_on opengl gui
QT                += core opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES = main.cpp

target.path = ./usb_machine
INSTALLS += target

#QMAKE_CXXFLAGS_RELEASE += -O3

LIBS += -L../lib -lusb_machine -lqwtplot3d

win32 {
    LIBS += -L$${SRC_DIR}/static/lib/ -lusb-1.0
} else {
    LIBS += -lusb-1.0
}

