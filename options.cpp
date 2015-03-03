#include "options.h"

Options::Options(QObject *parent) : QObject(parent) {
    settings = new QSettings();
}

Options::~Options() {
    delete settings;
}

double Options::getDimension() {
    return settings->value("dimension", DEFAULT_DIMMENSION).toDouble();
}

double Options::getXArea() {
    return settings->value("x_arae", DEFAULT_Z_AREA).toDouble();
}

double Options::getYArea() {
    return settings->value("y_arae", DEFAULT_Y_AREA).toDouble();
}

double Options::getZArea() {
    return settings->value("z_arae", DEFAULT_Z_AREA).toDouble();
}

double Options::getFArea() {
    return settings->value("f_arae", DEFAULT_F_AREA).toDouble();
}

double Options::getBlankArea() {
    return settings->value("blank_arae", DEFAULT_BLANK_AREA).toDouble();
}

void Options::setDimension(double value) {
    settings->setValue("dimension", value);
}

void Options::setXArea(double value) {
    settings->setValue("x_arae", value);
}

void Options::setYArea(double value) {
    settings->setValue("y_arae", value);
}

void Options::setZArea(double value) {
    settings->setValue("z_arae", value);
}

void Options::setFArea(double value) {
    settings->setValue("f_arae", value);
}

void Options::setBlankArea(double value) {
    settings->setValue("blank_arae", value);
}
