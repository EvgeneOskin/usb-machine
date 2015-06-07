#include <QtTest/QtTest>
#include <testoptions.h>
#include <usb/testtrackdataformatter.h>
#include <parser/testcompiler.h>

int main() {
    TestOptions test1;
    TestTrackDataFormatter test2;
    TestCompiler test3;

    QTest::qExec (&test1);
    QTest::qExec (&test2);
    QTest::qExec (&test3);
    return 0;
}
