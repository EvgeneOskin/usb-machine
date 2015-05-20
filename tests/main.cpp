#include <QtTest/QtTest>
#include <testoptions.h>

int main() {
    TestOptions test1;
    QTest::qExec(&test1);
    return 0;
}
