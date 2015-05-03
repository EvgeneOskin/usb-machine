#ifndef MANUALCONTROL_H
#define MANUALCONTROL_H

#include <QtWidgets>
#include <memory>

namespace Ui {
    class ManualControl;
}

class ManualControl : public QDialog
{
    Q_OBJECT
public:
    explicit ManualControl(QWidget *parent = 0);
    ~ManualControl();

signals:
    void apply(double x, double y, double z, double f);
    void requestReset();

public slots:
    void reset(double x, double y, double z, double f);

private slots:
    void buttonClicked(QAbstractButton* button);

private:
    const std::unique_ptr<Ui::ManualControl> ui;
    const QDoubleValidator xValidator;
    const QDoubleValidator yValidator;
    const QDoubleValidator zValidator;
    const QDoubleValidator fValidator;

    void applyCoordinates();
    void resetCoordinates();

};

#endif // MANUALCONTROL_H
