#include <QtTest>
#include "testcompiler.h"
#include <fstream>
#include <cmath>
#include "parser/compilator.h"

void TestCompiler::parserError(QString str) {
    qDebug(str.toStdString ().c_str ());
}

void TestCompiler::testSplines() {
    const char *filename = "test.dat";
    std::ofstream output(filename);

    output << "a = (0 0, 1 1, 2 exp(2)) x=a() y = 0\n"
              "b = (1 1, 20.0 cos(pi*1)) \n"
              "y = b()\n";

    output.close();

    Compilator compilator(filename);
    compilator.compile ();
    connect(&compilator, SIGNAL(parserError(QString)), this, SLOT(parserError(QString)));


    QVERIFY(!compilator.isErrorHappen());

    lines_t *lines = compilator.getLines ();
    QCOMPARE(lines->size (), 3u);

    lines_t::iterator it = lines->begin ();
    Value valueX1 = (*it)->find(std::string("x"))->second;
    QVERIFY(valueX1.getType () == value_types_spline);
    spline_nodes_t nodesX1 = valueX1.get_spline()->get_nodes ();
    QCOMPARE(nodesX1.size (), 3u);
    spline_nodes_t::iterator itNodeX1 = nodesX1.begin ();
    QCOMPARE((*itNodeX1)->first, 0.0);
    QCOMPARE((*itNodeX1)->second, 0.0);

    itNodeX1++;
    QCOMPARE((*itNodeX1)->first, 1.0);
    QCOMPARE((*itNodeX1)->second, 1.0);

    itNodeX1++;
    QCOMPARE((*itNodeX1)->first, 2.0);
    QCOMPARE((*itNodeX1)->second, exp(2.0));

    Value valueY1 = (*it)->find(std::string("y"))->second;
    QVERIFY(valueY1.getType () == value_types_number);
    QCOMPARE(valueY1.get_number (), 0.0);
    it++;

    Value valueX2 = (*it)->find(std::string("x"))->second;
    QVERIFY(valueX2.getType () == value_types_number);
    QCOMPARE(valueX2.get_number (), exp(2.0));

    Value valueY2 = (*it)->find(std::string("y"))->second;
    QVERIFY(valueY2.getType () == value_types_number);
    QCOMPARE(valueY2.get_number (), 0.0);

    it++;

    Value valueX3 = (*it)->find(std::string("x"))->second;
    QVERIFY(valueX3.getType () == value_types_number);
    QCOMPARE(valueX3.get_number(), exp(2.0));

    Value valueY3 = (*it)->find(std::string("y"))->second;
    QVERIFY(valueY3.getType () == value_types_spline);
    spline_nodes_t nodesY3 = valueY3.get_spline()->get_nodes ();
    QCOMPARE(nodesY3.size (), 2u);
    spline_nodes_t::iterator itNodeY3 = nodesY3.begin ();
    QCOMPARE((*itNodeY3)->first, 1.0);
    QCOMPARE((*itNodeY3)->second, 1.0);

    itNodeY3++;
    QCOMPARE((*itNodeY3)->first, 20.0);
    QCOMPARE((*itNodeY3)->second, -1.0);
}


void TestCompiler::testComments() {
    const char *filename = "test.dat";
    std::ofstream output(filename);

    output << "x=2/2*exp(0) y = 0    ;; comment 1\n"
              "*1 ;; loop\n"
              "x = 23 ; comment 213\n"
              "*\n"
              ;

    output.close();

    Compilator compilator(filename);
    compilator.compile ();
    connect(&compilator, SIGNAL(parserError(QString)), this, SLOT(parserError(QString)));


    QVERIFY(!compilator.isErrorHappen());

    lines_t *lines = compilator.getLines ();
    QCOMPARE(lines->size (), 2u);

    lines_t::iterator it = lines->begin ();
    Value valueX1 = (*it)->find(std::string("x"))->second;
    QVERIFY(valueX1.getType () == value_types_number);
    QCOMPARE(valueX1.get_number (), 1.0);

    Value valueY1 = (*it)->find(std::string("y"))->second;
    QVERIFY(valueY1.getType () == value_types_number);
    QCOMPARE(valueY1.get_number (), 0.0);
    it++;

    Value valueX2 = (*it)->find(std::string("x"))->second;
    QVERIFY(valueX2.getType () == value_types_number);
    QCOMPARE(valueX2.get_number(), 23.0);

    Value valueY2 = (*it)->find(std::string("y"))->second;
    QVERIFY(valueY2.getType () == value_types_number);
    QCOMPARE(valueY2.get_number(), 0.0);
}
