#include "optionswidget.h"
#include "ui_options.h"

OptionsWidget::OptionsWidget(QWidget *parent) :
    QDialog(parent), options(new Options), ui(new Ui::OptionsDialog) {

    ui->setupUi(this);

    ui->xLengthEdit->setValidator (&xLengthValidator);
    ui->xScaleEdit->setValidator (&xScaleValidator);
    ui->xVelocityScaleEdit->setValidator (&xVelocityScaleValidator);
    ui->xMaxVelocityEdit->setValidator (&xMaxVelocityValidator);

    ui->yLengthEdit->setValidator (&yLengthValidator);
    ui->yScaleEdit->setValidator (&yScaleValidator);
    ui->yVelocityScaleEdit->setValidator (&yVelocityScaleValidator);
    ui->yMaxVelocityEdit->setValidator (&yMaxVelocityValidator);

    ui->zLengthEdit->setValidator (&zLengthValidator);
    ui->zScaleEdit->setValidator (&zScaleValidator);
    ui->zVelocityScaleEdit->setValidator (&zVelocityScaleValidator);
    ui->zMaxVelocityEdit->setValidator (&zMaxVelocityValidator);

    ui->fLengthEdit->setValidator (&fLengthValidator);
    ui->fScaleEdit->setValidator (&fScaleValidator);
    ui->fVelocityScaleEdit->setValidator (&fVelocityScaleValidator);
    ui->fMaxVelocityEdit->setValidator (&fMaxVelocityValidator);


    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(closeAndWriteSettings()));
    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(buttonClicked(QAbstractButton*)));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(closeAndReadSettings()));

    readSettings();
}

OptionsWidget::~OptionsWidget() {}

void OptionsWidget::buttonClicked(QAbstractButton* button) {
    switch (ui->buttonBox->buttonRole (button)) {
    case QDialogButtonBox::ApplyRole:
        writeSettings ();
        break;
    default:
        break;
    }
}

void setTextDouble(QLineEdit* edit, double d) {
    QString s;
    s.setNum (d);
    edit->setText (s);
}

void setTextUint16(QLineEdit* edit, uint16_t ui16) {
    QString s;
    s.setNum (ui16);
    edit->setText (s);
}

double getDimension(QRadioButton *mm, QRadioButton *sm, QRadioButton *m){
    if (mm->isChecked()) {
      return 1e-3;
    } else if (sm->isChecked()) {
      return 1e-2;
    } else if (m->isChecked()) {
      return 1;
    }
    return 0.0;
}

void setDimension(QRadioButton *mm, QRadioButton *sm,  QRadioButton *m, double d){
    if (d == 1e-3) {
        mm->setChecked(true);
    } else if (d == 1e-2) {
        sm->setChecked(true);
    } else if (d == 1){
        m->setChecked(true);
    }
}


void OptionsWidget::readSettings() {
    setDimension (ui->mmCheckBox, ui->smCheckBox,
                  ui->mCheckBox, options->getDimension ());

    setTextDouble (ui->xLengthEdit, options->getXArea ());
    setTextUint16 (ui->xScaleEdit, options->getXScale());
    setTextUint16 (ui->xVelocityScaleEdit, options->getVelocityXScale ());
    setTextDouble (ui->xMaxVelocityEdit, options->getMaxVelocityX ());

    setTextDouble (ui->yLengthEdit, options->getYArea ());
    setTextUint16 (ui->yScaleEdit, options->getYScale());
    setTextUint16 (ui->yVelocityScaleEdit, options->getVelocityYScale ());
    setTextDouble (ui->yMaxVelocityEdit, options->getMaxVelocityY ());

    setTextDouble (ui->zLengthEdit, options->getZArea ());
    setTextUint16 (ui->zScaleEdit, options->getZScale());
    setTextUint16 (ui->zVelocityScaleEdit, options->getVelocityZScale ());
    setTextDouble (ui->zMaxVelocityEdit, options->getMaxVelocityZ ());

    setTextDouble (ui->fLengthEdit, options->getFArea ());
    setTextUint16 (ui->fScaleEdit, options->getFScale());
    setTextUint16 (ui->fVelocityScaleEdit, options->getVelocityFScale ());
    setTextDouble (ui->fMaxVelocityEdit, options->getMaxVelocityF ());
}

void OptionsWidget::closeAndWriteSettings() {
    writeSettings();
    hide();
}

void OptionsWidget::closeAndReadSettings() {
    readSettings();
    hide();
}

double getDoubleText(QLineEdit* edit) {
    return edit->text ().toDouble ();
}

uint16_t getUint16Text(QLineEdit* edit) {
    return (uint16_t ) edit->text ().toUShort ();
}


void OptionsWidget::writeSettings() {
    options->setDimension (getDimension (
        ui->mmCheckBox, ui->smCheckBox, ui->mCheckBox));

    options->setXArea(getDoubleText(ui->xLengthEdit));
    options->setXScale (getUint16Text (ui->xScaleEdit));
    options->setVelocityXScale (getUint16Text (ui->xVelocityScaleEdit));
    options->setMaxVelocityX (getDoubleText(ui->xMaxVelocityEdit));

    options->setYArea (getDoubleText(ui->yLengthEdit));
    options->setYScale (getUint16Text (ui->yScaleEdit));
    options->setVelocityYScale (getUint16Text (ui->yVelocityScaleEdit));
    options->setMaxVelocityY (getDoubleText(ui->yMaxVelocityEdit));

    options->setZArea (getDoubleText(ui->zLengthEdit));
    options->setZScale (getUint16Text (ui->zScaleEdit));
    options->setVelocityZScale (getUint16Text (ui->zVelocityScaleEdit));
    options->setMaxVelocityZ (getDoubleText(ui->zMaxVelocityEdit));

    options->setFArea (getDoubleText(ui->fLengthEdit));
    options->setFScale (getUint16Text (ui->fScaleEdit));
    options->setVelocityFScale (getUint16Text (ui->zVelocityScaleEdit));
    options->setMaxVelocityF (getDoubleText(ui->fMaxVelocityEdit));
}
