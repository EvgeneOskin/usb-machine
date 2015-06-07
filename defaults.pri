SRC_DIR = $$PWD

INCLUDEPATH += $$PWD/src
INCLUDEPATH += $$PWD/src/gsl

INCLUDEPATH += $$PWD/static/include

INCLUDEPATH += $$PWD/qwtplot3d/include

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11


unix:QMAKE_CXX="g++-4.8"
