#ifndef OPTIONS_H
#define OPTIONS_H

#include <QObject>
#include <QSettings>
#include <memory>

#define DEFAULT_DIMMENSION 1.0

#define DEFAULT_X_AREA 1.0
#define DEFAULT_X_VELOCITY_SCALE 1
#define DEFAULT_X_SCALE 1
#define DEFAULT_MAX_VELOCITY_X 1.0

#define DEFAULT_Y_AREA 1.0
#define DEFAULT_Y_VELOCITY_SCALE 1
#define DEFAULT_Y_SCALE 1
#define DEFAULT_MAX_VELOCITY_Y 1.0

#define DEFAULT_Z_AREA 1.0
#define DEFAULT_Z_VELOCITY_SCALE 1
#define DEFAULT_Z_SCALE 1
#define DEFAULT_MAX_VELOCITY_Z 1.0

#define DEFAULT_F_AREA 1.0
#define DEFAULT_F_VELOCITY_SCALE 1
#define DEFAULT_F_SCALE 1
#define DEFAULT_MAX_VELOCITY_F 1.0

#define DEFAULT_BLANK_AREA 1.0


class Options : public QObject
{
    Q_OBJECT
public:
    explicit Options(QObject *parent = 0);
    ~Options();

    double getDimension();
    void setDimension(double value);

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
    void setBlankArea(double value);

signals:

public slots:

private:
    std::unique_ptr<QSettings> settings;
};

#endif // OPTIONS_H
