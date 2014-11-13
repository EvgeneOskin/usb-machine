TEMPLATE = app
TARGET = usb_machine
CONFIG            += qt warn_on thread opengl warn_on
QT                += widgets core opengl

MOC_DIR           = tmp
OBJECTS_DIR       = tmp

DEPENDPATH += qwtplot3d

HEADERS = mainwindow.h \
    mainwidget.h \
    customedittext.h \
    optionswidget.h \
    mainoptions.h \
    machineoptions.h \
    codehighlighter.h \
    jenia.h \
    compilator.h \
    DEF.h \
    Parser.h \
    parsertypes.h \
    ast.h \
    modeling.h \
    usbconnection.h \
    highlightrule.h \
    instrumentwidget.h \
    searchwidget.h \
    usbtool.h \
    track.h

SOURCES = main.cpp \
    mainwindow.cpp \
    mainwidget.cpp \
    customedittext.cpp \
    optionswidget.cpp \
    mainoptions.cpp \
    machineoptions.cpp \
    codehighlighter.cpp \
    jenia.cpp \
    compilator.cpp \
    func.cpp \
    lex.yy.cpp \
    Parser.cpp \
    ast.cpp \
    usbconnection.cpp \
    highlightrule.cpp \
    instrumentwidget.cpp \
    modeling.cpp \
    searchwidget.cpp \
    usbtool.cpp \
    track.cpp

target.path = ./usb_machine
INSTALLS += target

#QMAKE_CXXFLAGS_RELEASE += -O3


win32 {
    LIBS += -L$$PWD/static/lib/ -lusb-1.0
    LIBS += -L"C:/Program Files (x86)/GnuWin32/lib" -lfl
} else {
    LIBS += -lusb-1.0
    LIBS += -lfl
}
LIBS += -L$$PWD/qwtplot3d/lib/ -lqwtplot3d

INCLUDEPATH += $$PWD/qwtplot3d/include/
INCLUDEPATH += $$PWD/static/include

