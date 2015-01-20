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
    usbconnection.h \
    highlightrule.h \
    instrumentwidget.h \
    searchwidget.h \
    usbtool.h \
    plotwidget.h \
    modeling/track.h \
    modeling/modeling.h \
    modeling/tracksegment.h \
    modeling/splinesegment.h \
    modeling/tracksegment3d.h

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
    searchwidget.cpp \
    usbtool.cpp \
    plotwidget.cpp \
    modeling/track.cpp \
    modeling/modeling.cpp \
    modeling/tracksegment.cpp \
    modeling/splinesegment.cpp \
    modeling/tracksegment3d.cpp

target.path = ./usb_machine
INSTALLS += target

#QMAKE_CXXFLAGS_RELEASE += -O3


win32 {
    LIBS += -L"C:/gnuwin32/lib" -lfl
    LIBS += -L"C:/gnuwin32/lib" -lgsl
    LIBS += -lglew32
    LIBS += -L$$PWD/static/lib/ -lusb-1.0
    INCLUDEPATH += "C:/gnuwin32/include"
} else {
    LIBS += -lusb-1.0
    LIBS += -lfl
    LIBS += -lgsl -lgslcblas
    LIBS += -lopengl
}

INCLUDEPATH += $$PWD/qwtplot3d/include
LIBS += -L$$PWD/lib/ -lqwtplot3d

INCLUDEPATH += $$PWD/parser
LIBS += -L$$PWD/parser/ -lparser

INCLUDEPATH += $$PWD/static/include
