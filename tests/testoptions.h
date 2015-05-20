#ifndef TESTOPTIONS_H
#define TESTOPTIONS_H

#include <QtTest/QtTest>
#include <QObject>

class TestOptions : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void cleanupTestCase();
};

#endif // TESTOPTIONS_H
