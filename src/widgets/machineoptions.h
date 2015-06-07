#ifndef MACHINEOPTIONS_H
#define MACHINEOPTIONS_H

#include <QtWidgets>

class MachineOptions : public QWidget
{
    Q_OBJECT
public:
    explicit MachineOptions(QWidget *parent = 0);

    double getXArea();
    void setXArea(double value);
    uint16_t getVelocityXScale();
    void setVelocityXScale(uint16_t value);
    uint16_t getXScale();
    void setXScale(uint16_t value);
    double getMaxVelocityX();
    void setMaxVelocityX(double value);

    double getYArea();
    void setYArea(double value);
    uint16_t getVelocityYScale();
    void setVelocityYScale(uint16_t value);
    uint16_t getYScale();
    void setYScale(uint16_t value);
    double getMaxVelocityY();
    void setMaxVelocityY(double value);

    double getZArea();
    void setZArea(double value);
    uint16_t getVelocityZScale();
    void setVelocityZScale(uint16_t value);
    uint16_t getZScale();
    void setZScale(uint16_t value);
    double getMaxVelocityZ();
    void setMaxVelocityZ(double value);

    double getFArea();
    void setFArea(double value);
    uint16_t getVelocityFScale();
    void setVelocityFScale(uint16_t value);
    uint16_t getFScale();
    void setFScale(uint16_t value);
    double getMaxVelocityF();
    void setMaxVelocityF(double value);

    double getBlankArea();
    void setBlankArea(double blank);

private:
    QVBoxLayout* machineLayout;

    QLineEdit* xAreaEdit;
    QLineEdit* velocityXScaleEdit;
    QLineEdit* xScaleEdit;
    QLineEdit* maxVelocityXEdit;

    QLineEdit* yAreaEdit;
    QLineEdit* velocityYScaleEdit;
    QLineEdit* yScaleEdit;
    QLineEdit* maxVelocityYEdit;

    QLineEdit* zAreaEdit;
    QLineEdit* velocityZScaleEdit;
    QLineEdit* zScaleEdit;
    QLineEdit* maxVelocityZEdit;

    QLineEdit* fAreaEdit;
    QLineEdit* velocityFScaleEdit;
    QLineEdit* fScaleEdit;
    QLineEdit* maxVelocityFEdit;

    QLineEdit* blankAreaEdit;

    void createMachineLayout();
    void makeTempLayout(
            QBoxLayout *child, QString lableStr,
            QLineEdit* edit, QBoxLayout* parent);

signals:

public slots:

};

#endif // MACHINEOPTIONS_H
