include(../defaults.pri)

TEMPLATE = lib
TARGET = usb_machine
CONFIG += qt warn_on opengl gui
QT += core opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR = ../lib

CONFIG += lex
QMAKE_LEX = flex
LEXSOURCES += parser/flex.l


CONFIG += yacc
QMAKE_YACC = bison
YACCSOURCES += parser/grammar.yy
QMAKE_YACC_HEADER = grammar.tab.h
QMAKE_YACC_SOURCE = grammar.tab.c
QMAKE_YACCFLAGS_MANGLE  += -p $base -b $base

HEADERS = mainwindow.h \
    mainwidget.h \
    customedittext.h \
    codehighlighter.h \
    highlightrule.h \
    instrumentwidget.h \
    searchwidget.h \
    modeling/track.h \
    modeling/modeling.h \
    modeling/tracksegment.h \
    modeling/splinesegment.h \
    usb/connection.h \
    usb/trackdataformatter.h \
    usb/dataformatter.h \
    usb/axisrange.h \
    usb/trackmodelingwrapper.h \
    usb/idgenerator.h \
    usb/usbmesaagetypes.h \
    options.h \
    widgets/plotwidget.h \
    widgets/optionswidget.h \
    gsl/templates_on.h \
    gsl/templates_off.h \
    gsl/gsl_types.h \
    gsl/gsl_pow_int.h \
    gsl/gsl_nan.h \
    gsl/gsl_minmax.h \
    gsl/gsl_math.h \
    gsl/gsl_inline.h \
    gsl/gsl_errno.h \
    gsl/gsl_block_double.h \
    gsl/config.h \
    gsl/build.h \
    gsl/interpolation/integ_eval.h \
    gsl/interpolation/gsl_spline.h \
    gsl/interpolation/gsl_interp.h \
    gsl/linalg/gsl_linalg.h \
    gsl/vector/view.h \
    gsl/vector/gsl_vector_double.h \
    gsl/vector/gsl_vector.h \
    widgets/manualcontrol.h \
    parser/parserspline.h \
    parser/parsertypes.h \
    parser/ast.h \
    parser/parser_value.h \
    modeling/abstracttrack.h \
    modeling/modelingvectortypes.h \
    modeling/tracksegment4d.h \
    parser/compilator.h

SOURCES = mainwindow.cpp \
    mainwidget.cpp \
    customedittext.cpp \
    codehighlighter.cpp \
    highlightrule.cpp \
    instrumentwidget.cpp \
    searchwidget.cpp \
    modeling/track.cpp \
    modeling/modeling.cpp \
    modeling/tracksegment.cpp \
    modeling/splinesegment.cpp \
    parser/parsertypes.cpp \
    parser/ast.cpp \
    parser/parserspline.cpp \
    parser/parser_value.cpp \
    usb/connection.cpp \
    usb/trackdataformatter.cpp \
    usb/dataformatter.cpp \
    usb/axisrange.cpp \
    usb/trackmodelingwrapper.cpp \
    usb/idgenerator.cpp \
    usb/usbmesaagetypes.cpp \
    options.cpp \
    widgets/plotwidget.cpp \
    widgets/optionswidget.cpp \
    gsl/interpolation/spline.c \
    gsl/interpolation/linear.c \
    gsl/interpolation/interp.c \
    gsl/interpolation/inline.c \
    gsl/interpolation/cspline.c \
    gsl/interpolation/accel.c \
    gsl/linalg/tridiag.c \
    gsl/vector/view_source.c \
    gsl/vector/view.c \
    widgets/manualcontrol.cpp \
    modeling/abstracttrack.cpp \
    modeling/modelingvectortypes.cpp \
    modeling/tracksegment4d.cpp \
    parser/compilator.cpp


#QMAKE_CXXFLAGS_RELEASE += -O3


win32 {
#    LIBS += -L"C:/gnuwin32/lib" -lgsl -lgslcblas
    LIBS += -lglew32
    LIBS += -L$${SRC_DIR}/static/lib/ -lusb-1.0
#    INCLUDEPATH += "C:/gnuwin32/include"
} else {
    LIBS += -lusb-1.0
    LIBS += -lfl
    LIBS += -lGL -lGLU -lglut -lGLEW
}

LIBS += -L ../lib -lqwtplot3d

FORMS += \
    manualcontrol.ui \
    options.ui
