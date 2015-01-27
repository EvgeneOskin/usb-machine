#ifndef COMPILATOR_H
#define COMPILATOR_H

#include "grammar_yacc.h"
#include <string>
#include <cstdio>
#include <QObject>
#include <QString>

class Compilator : public QObject, public Parser {
    Q_OBJECT

public:
    Compilator(const char* filename);
    ~Compilator();
    void compile();
    lines_t* getLines();
    int handleError(const char *msg,
                     int first_line, int first_column,
                     int last_line, int last_column);
    bool isErrorHappen();

signals:
    void parserError(QString error);

private:
    FILE* inputFile = NULL;
    bool errorHappen;
};

#endif // COMPILATOR_H
