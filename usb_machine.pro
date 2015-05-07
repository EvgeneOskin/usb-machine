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
    usb/connection.h \
    usb/trackdataformatter.h \
    usb/dataformatter.h \
    usb/usbtypes.h \
    usb/axisrange.h \
    widgets/machineoptions.h \
    widgets/mainoptions.h \
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
    parser/parserspline.hpp

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
    usb/connection.cpp \
    usb/trackdataformatter.cpp \
    usb/dataformatter.cpp \
    usb/axisrange.cpp \
    widgets/machineoptions.cpp \
    widgets/mainoptions.cpp \
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
    parser/parserspline.cpp


target.path = ./usb_machine
INSTALLS += target

#QMAKE_CXXFLAGS_RELEASE += -O3


win32 {
    LIBS += -L"C:/gnuwin32/lib" -lfl
#    LIBS += -L"C:/gnuwin32/lib" -lgsl -lgslcblas
    LIBS += -lglew32
    LIBS += -L$$PWD/static/lib/ -lusb-1.0
#    INCLUDEPATH += "C:/gnuwin32/include"
} else {
    LIBS += -lusb-1.0
    LIBS += -lfl
    LIBS += -lopengl
}

INCLUDEPATH += $$PWD/qwtplot3d/include
LIBS += -L$$PWD/lib/ -lqwtplot3d

INCLUDEPATH += $$PWD/static/include

INCLUDEPATH += $$PWD/gsl
