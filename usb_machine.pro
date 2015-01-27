TEMPLATE = app
TARGET = usb_machine
CONFIG            += qt warn_on opengl
QT                += widgets core opengl

CONFIG += lex yacc

QMAKE_LEX = flex
QMAKE_YACC = bison

LEXSOURCES += parser/flex.l
YACCSOURCES += parser/grammar.yy
lex_impl.CONFIG += target_predeps
yacc_impl.CONFIG += target_predeps
yacc_decl.CONFIG += target_predeps

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
    modeling/tracksegment3d.h \
    parser/ast.hpp \
    parser/parser_value.hpp \
    parser/parsertypes.hpp \
    parser/spline.hpp

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
    modeling/tracksegment3d.cpp \
    parser/parsertypes.cpp \
    parser/ast.cpp \
    parser/parser_value.cpp \
    parser/spline.cpp


target.path = ./usb_machine
INSTALLS += target

#QMAKE_CXXFLAGS_RELEASE += -O3


win32 {
    LIBS += -L"C:/gnuwin32/lib" -lfl
    LIBS += -L"C:/gnuwin32/lib" -lgsl -lgslcblas
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
LIBS += -L$$PWD/qwtplot3d/lib/ -lqwtplot3d

INCLUDEPATH += $$PWD/static/include
