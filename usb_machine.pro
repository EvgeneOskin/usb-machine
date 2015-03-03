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
    codehighlighter.h \
    compilator.h \
    highlightrule.h \
    instrumentwidget.h \
    searchwidget.h \
    modeling/track.h \
    modeling/modeling.h \
    modeling/tracksegment.h \
    modeling/splinesegment.h \
    modeling/tracksegment3d.h \
    parser/ast.hpp \
    parser/parser_value.hpp \
    parser/parsertypes.hpp \
    parser/spline.hpp \
    usb/connection.h \
    usb/trackdataformatter.h \
    usb/dataformatter.h \
    usb/usbtypes.h \
    usb/axisrange.h \
    widgets/machineoptions.h \
    widgets/mainoptions.h \
    options.h \
    widgets/plotwidget.h \
    widgets/optionswidget.h

SOURCES = main.cpp \
    mainwindow.cpp \
    mainwidget.cpp \
    customedittext.cpp \
    codehighlighter.cpp \
    compilator.cpp \
    highlightrule.cpp \
    instrumentwidget.cpp \
    searchwidget.cpp \
    modeling/track.cpp \
    modeling/modeling.cpp \
    modeling/tracksegment.cpp \
    modeling/splinesegment.cpp \
    modeling/tracksegment3d.cpp \
    parser/parsertypes.cpp \
    parser/ast.cpp \
    parser/parser_value.cpp \
    parser/spline.cpp \
    usb/connection.cpp \
    usb/trackdataformatter.cpp \
    usb/dataformatter.cpp \
    usb/axisrange.cpp \
    widgets/machineoptions.cpp \
    widgets/mainoptions.cpp \
    options.cpp \
    widgets/plotwidget.cpp \
    widgets/optionswidget.cpp


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
