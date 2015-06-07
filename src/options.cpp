#include "options.h"

Options::Options(QObject *parent) : QObject(parent), settings(new QSettings) {
}

Options::~Options() { }

double Options::getDimension() {
    return settings->value("dimension", (DEFAULT_DIMMENSION)).toDouble();
}

void Options::setDimension(double value) {
    settings->setValue("dimension", value);
}

double Options::getBlankArea() {
    return settings->value("blank_arae", (DEFAULT_BLANK_AREA)).toDouble();
}

void Options::setBlankArea(double value) {
    settings->setValue("blank_arae", value);
}

double Options::getXArea() {
    return settings->value("x_arae", (DEFAULT_Z_AREA)).toDouble();
}

void Options::setXArea(double value) {
    settings->setValue("x_arae", value);
}

uint16_t Options::getVelocityXScale() {
    return settings->value("x_velocity_scale", (DEFAULT_X_VELOCITY_SCALE)).toUInt();
}

void Options::setVelocityXScale(uint16_t value) {
    settings->setValue("x_velocity_scale", value);
}

uint16_t Options::getXScale() {
    return settings->value("x_scale", (DEFAULT_X_SCALE)).toUInt();
}

void Options::setXScale(uint16_t value) {
    settings->setValue("x_scale", value);
}

double Options::getMaxVelocityX () {
    return settings->value("max_velocity_x", (DEFAULT_MAX_VELOCITY_X)).toDouble();
}

void Options::setMaxVelocityX (double value) {
    settings->setValue("max_velocity_x", value);
}

double Options::getYArea() {
    return settings->value("y_arae", (DEFAULT_Y_AREA)).toDouble();
}

void Options::setYArea(double value) {
    settings->setValue("y_arae", value);
}

uint16_t Options::getVelocityYScale() {
    return settings->value("y_velocity_scale", (DEFAULT_Y_VELOCITY_SCALE)).toUInt();
}

void Options::setVelocityYScale(uint16_t value) {
    settings->setValue("y_velocity_scale", value);
}
uint16_t Options::getYScale() {
    return settings->value("y_scale", (DEFAULT_Y_SCALE)).toUInt();
}

void Options::setYScale(uint16_t value) {
    settings->setValue("y_scale", value);
}

double Options::getMaxVelocityY () {
    return settings->value("max_velocity_y", (DEFAULT_MAX_VELOCITY_Y)).toDouble();
}

void Options::setMaxVelocityY (double value) {
    settings->setValue("max_velocity_y", value);
}

double Options::getZArea() {
    return settings->value("z_arae", (DEFAULT_Z_AREA)).toDouble();
}

void Options::setZArea(double value) {
    settings->setValue("z_arae", value);
}

uint16_t Options::getVelocityZScale() {
    return settings->value("z_velocity_scale", (DEFAULT_Z_VELOCITY_SCALE)).toUInt();
}

void Options::setVelocityZScale(uint16_t value) {
    settings->setValue("z_velocity_scale", value);
}

uint16_t Options::getZScale() {
    return settings->value("z_scale", (DEFAULT_Z_SCALE)).toUInt();
}

void Options::setZScale(uint16_t value) {
    settings->setValue("z_scale", value);
}

double Options::getMaxVelocityZ () {
    return settings->value("max_velocity_z", (DEFAULT_MAX_VELOCITY_Z)).toDouble();
}

void Options::setMaxVelocityZ (double value) {
    settings->setValue("max_velocity_z", value);
}

double Options::getFArea() {
    return settings->value("f_arae", (DEFAULT_F_AREA)).toDouble();
}

void Options::setFArea(double value) {
    settings->setValue("f_arae", value);
}

uint16_t Options::getVelocityFScale() {
    return settings->value("f_velocity_scale", (DEFAULT_F_VELOCITY_SCALE)).toUInt();
}

void Options::setVelocityFScale(uint16_t value) {
    settings->setValue("f_velocity_scale", value);
}

uint16_t Options::getFScale() {
    return settings->value("f_scale", (DEFAULT_F_SCALE)).toUInt();
}

void Options::setFScale(uint16_t value) {
    settings->setValue("f_scale", value);
}

double Options::getMaxVelocityF () {
    return settings->value("max_velocity_f", (DEFAULT_MAX_VELOCITY_F)).toDouble();
}

void Options::setMaxVelocityF (double value) {
    settings->setValue("max_velocity_f", value);
}
