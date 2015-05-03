include(../defaults.pri)

TEMPLATE = lib
TARGET = usb_machine
CONFIG += qt warn_on opengl
QT += widgets core opengl


DESTDIR = ../lib

CONFIG += lex
QMAKE_LEX = flex
LEXSOURCES += parser/flex.l
lex.CONFIG += target_predeps

CONFIG += yacc
QMAKE_YACC = bison
YACCSOURCES += parser/grammar.yy
yacc_impl.CONFIG += target_predeps
yacc_decl.CONFIG += target_predeps

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
    modeling/tracksegment4d.h

SOURCES = mainwindow.cpp \
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
    modeling/tracksegment4d.cpp


#QMAKE_CXXFLAGS_RELEASE += -O3


win32 {
#    LIBS += -L"C:/gnuwin32/lib" -lgsl -lgslcblas
    LIBS += -lglew32
    LIBS += -L$${SRC_DIR}/static/lib/ -lusb-1.0
#    INCLUDEPATH += "C:/gnuwin32/include"
} else {
    LIBS += -lusb-1.0
    LIBS += -lfl
    LIBS += -lopengl
}

LIBS += -L../lib/ -lqwtplot3d

FORMS += \
    manualcontrol.ui \
    options.ui
