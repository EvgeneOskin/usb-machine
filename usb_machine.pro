TEMPLATE = subdirs
CONFIG+=ordered
SUBDIRS = \
    qwtplot3d \
    src \
    app \
    tests
src.depends = qwtplot3d
app.depends = src
tests.depends = src

DISTFILES += \
    defaults.pri

