#ifndef TESTCOMPILER_H
#define TESTCOMPILER_H

#include <QObject>

class TestCompiler : public QObject {

    Q_OBJECT

private slots:
    void parserError(QString str);
    void testSplines();
};

#endif // TESTCOMPILER_H
