#ifndef OPTIONS_H
#define OPTIONS_H

#include <QObject>
#include <QSettings>

#define DEFAULT_DIMMENSION 1
#define DEFAULT_X_AREA 1
#define DEFAULT_Y_AREA 1
#define DEFAULT_Z_AREA 1
#define DEFAULT_F_AREA 1
#define DEFAULT_BLANK_AREA 1


class Options : public QObject
{
    Q_OBJECT
public:
    explicit Options(QObject *parent = 0);
    ~Options();

    double getDimension();
    double getXArea();
    double getYArea();
    double getZArea();
    double getFArea();
    double getBlankArea();

    void setDimension(double value);
    void setXArea(double value);
    void setYArea(double value);
    void setZArea(double value);
    void setFArea(double value);
    void setBlankArea(double value);

signals:

public slots:

private:
    QSettings *settings;
};

#endif // OPTIONS_H
