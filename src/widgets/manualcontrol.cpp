#include "manualcontrol.h"
#include "ui_manualcontrol.h"

ManualControl::ManualControl(QWidget *parent)
    : QDialog(parent), ui(new Ui::ManualControl),
      xValidator(), yValidator(), zValidator(), fValidator() {

    getUi()->setupUi (this);
    getUi()->coordinateXEdit->setValidator (&xValidator);
    getUi()->coordinateYEdit->setValidator (&yValidator);
    getUi()->coordinateZEdit->setValidator (&zValidator);
    getUi()->coordinateFEdit->setValidator (&fValidator);

    connect(getUi()->buttonBox, SIGNAL(clicked), this, SLOT(buttonClicked));
    connect(getUi()->buttonBox, SIGNAL(refected), this, SLOT(hide));
}

ManualControl::~ManualControl() {
}

Ui::ManualControl* ManualControl::getUi () {
    return ui.get();
}

void ManualControl::buttonClicked(QAbstractButton* button) {
    switch(getUi()->buttonBox->standardButton (button)) {
    case QDialogButtonBox::Apply:
        applyCoordinates();
        break;
    case QDialogButtonBox::Reset:
        resetCoordinates();
        break;
    default:
        break;
    }
    return;
}

double getDoubleFromEdit(QLineEdit *edit) {
    return edit->text().toDouble ();
}

void ManualControl::applyCoordinates() {
    double x, y, z, f;

    x = getDoubleFromEdit(getUi()->coordinateXEdit);
    y = getDoubleFromEdit(getUi()->coordinateYEdit);
    z = getDoubleFromEdit(getUi()->coordinateZEdit);
    f = getDoubleFromEdit(getUi()->coordinateFEdit);

    emit apply(x, y, z, f);
}

void ManualControl::resetCoordinates() {
    emit requestReset();
}

void setDoubleToEdit(double value, QLineEdit *edit) {
    QString str;
    str.setNum (value);
    edit->setText (str);
}

void ManualControl::reset(double x, double y, double z, double f) {
    setDoubleToEdit(x, getUi()->coordinateXEdit);
    setDoubleToEdit(y, getUi()->coordinateYEdit);
    setDoubleToEdit(z, getUi()->coordinateZEdit);
    setDoubleToEdit(f, getUi()->coordinateFEdit);
}
