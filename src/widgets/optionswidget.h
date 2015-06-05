#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include <QtWidgets>
#include <memory>
#include "options.h"

namespace Ui {
    class OptionsDialog;
}


class OptionsWidget : public QDialog {
    Q_OBJECT

public:
    OptionsWidget(QWidget *parent=0);
    ~OptionsWidget();

private:
    std::unique_ptr<Options> options;
    std::unique_ptr<Ui::OptionsDialog> ui;

    QDoubleValidator xLengthValidator;
    QIntValidator xScaleValidator;
    QIntValidator xVelocityScaleValidator;
    QDoubleValidator xMaxVelocityValidator;

    QDoubleValidator yLengthValidator;
    QIntValidator yScaleValidator;
    QIntValidator yVelocityScaleValidator;
    QDoubleValidator yMaxVelocityValidator;

    QDoubleValidator zLengthValidator;
    QIntValidator zScaleValidator;
    QIntValidator zVelocityScaleValidator;
    QDoubleValidator zMaxVelocityValidator;

    QDoubleValidator fLengthValidator;
    QIntValidator fScaleValidator;
    QIntValidator fVelocityScaleValidator;
    QDoubleValidator fMaxVelocityValidator;

public slots:
    void readSettings();
    void writeSettings();
    void closeAndWriteSettings();
    void closeAndReadSettings();

private slots:
    void buttonClicked(QAbstractButton* button);


};
#endif // OPTIONSWIDGET_H
