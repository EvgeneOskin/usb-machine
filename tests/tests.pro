include(../defaults.pri)

TEMPLATE = app
CONFIG += qt warn_on opengl
QT += widgets core opengl

tests.target = test

CONFIG += testcase
QT += testlib

CONFIG   -= app_bundle

SOURCES += main.cpp \
    testoptions.cpp \
    usb/testtrackdataformatter.cpp \
    parser/testcompiler.cpp

HEADERS += \
    testoptions.h \
    usb/testtrackdataformatter.h \
    parser/testcompiler.h

#QMAKE_CXXFLAGS_RELEASE += -O3

LIBS += -L../lib -lusb_machine -lqwtplot3d

win32 {
    LIBS += -L$${SRC_DIR}/static/lib/ -lusb-1.0
} else {
    LIBS += -lusb-1.0
}



