TEMPLATE = app
TARGET = usb_machine
CONFIG            += qt warn_on thread opengl warn_on
QT                += widgets core opengl


DEPENDPATH += qwtplot3d

HEADERS = mainwindow.h \
    mainwidget.h \
    customedittext.h \
    optionswidget.h \
    mainoptions.h \
    machineoptions.h \
    codehighlighter.h \
    compilator.h \
    modeling.h \
    usbconnection.h \
    highlightrule.h \
    instrumentwidget.h \
    searchwidget.h \
    usbtool.h \
    track.h \
    plotwidget.h

SOURCES = main.cpp \
    mainwindow.cpp \
    mainwidget.cpp \
    customedittext.cpp \
    optionswidget.cpp \
    mainoptions.cpp \
    machineoptions.cpp \
    codehighlighter.cpp \
    compilator.cpp \
    usbconnection.cpp \
    highlightrule.cpp \
    instrumentwidget.cpp \
    modeling.cpp \
    searchwidget.cpp \
    usbtool.cpp \
    track.cpp \
    plotwidget.cpp

target.path = ./usb_machine
INSTALLS += target

#QMAKE_CXXFLAGS_RELEASE += -O3


win32 {
    LIBS += -L$$PWD/static/lib/ -lusb-1.0
    LIBS += -L"C:/gnuwin32/lib" -lfl
    LIBS += -L"C:/gnuwin32/lib" -lgsl
    INCLUDEPATH += "C:/gnuwin32/include"
} else {
    LIBS += -lusb-1.0
    LIBS += -lfl
}
LIBS += -L$$PWD/qwtplot3d/lib/ -lqwtplot3d
LIBS += -lglew32
LIBS += -L$$PWD/parser/ -lparser

INCLUDEPATH += $$PWD/qwtplot3d/include
INCLUDEPATH += $$PWD/static/include
INCLUDEPATH += $$PWD/parser
