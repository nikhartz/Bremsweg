#include <QString>
#include <QtTest>
#include <libbremsweg.h>

class BremswegTest : public QObject
{
    Q_OBJECT

public:
    BremswegTest();

private Q_SLOTS:
    void testCase1();
};

BremswegTest::BremswegTest()
{
}

void BremswegTest::testCase1()
{

}

QTEST_APPLESS_MAIN(BremswegTest)

#include "tst_bremswegtest.moc"
