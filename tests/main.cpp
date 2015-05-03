#include <QtTest/QtTest>
#include <testoptions.h>
#include <usb/testtrackdataformatter.h>

int main() {
    TestOptions test1;
    TestTrackDataFormatter test2;
    QTest::qExec (&test1);
    QTest::qExec (&test2);
    return 0;
}
