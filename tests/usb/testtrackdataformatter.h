#ifndef TESTTRACKDATAFORMATTER_H
#define TESTTRACKDATAFORMATTER_H

#include <QtTest/QtTest>
#include <QObject>

class TestTrackDataFormatter : public QObject
{
    Q_OBJECT

private slots:
    void test2Points();
    void testPointAndSpline();
};

#endif // TESTTRACKDATAFORMATTER_H
