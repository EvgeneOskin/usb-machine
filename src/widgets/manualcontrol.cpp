#include "manualcontrol.h"
#include "ui_manualcontrol.h"

ManualControl::ManualControl(QWidget *parent)
    : QDialog(parent), ui(new Ui::ManualControl),
      xValidator(), yValidator(), zValidator(), fValidator() {

    ui->setupUi (this);
    ui->coordinateXEdit->setValidator (&xValidator);
    ui->coordinateYEdit->setValidator (&yValidator);
    ui->coordinateZEdit->setValidator (&zValidator);
    ui->coordinateFEdit->setValidator (&fValidator);

    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(buttonClicked(QAbstractButton*)));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(hide()));
}

ManualControl::~ManualControl() {
}

void ManualControl::buttonClicked(QAbstractButton* button) {
    switch(ui->buttonBox->standardButton (button)) {
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

    x = getDoubleFromEdit(ui->coordinateXEdit);
    y = getDoubleFromEdit(ui->coordinateYEdit);
    z = getDoubleFromEdit(ui->coordinateZEdit);
    f = getDoubleFromEdit(ui->coordinateFEdit);

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
    setDoubleToEdit(x, ui->coordinateXEdit);
    setDoubleToEdit(y, ui->coordinateYEdit);
    setDoubleToEdit(z, ui->coordinateZEdit);
    setDoubleToEdit(f, ui->coordinateFEdit);
}
