#include <QString>
#include <QtTest>
#include "libbremsweg.h"

class BremswegTest : public QObject
{
    Q_OBJECT

public:
    BremswegTest();

private Q_SLOTS:
    void testCase11();//Pkw, keine Gefahrenbremsung, trockener Boden, Geschwindigkeit 50
    void testCase12();//Pkw, keine Gefahrenbremsung, trockener Boden, Geschwindigkeit 70
    void testCase13();//Pkw, keine Gefahrenbremsung, nasser Boden, Geschwindigkeit 50
    void testCase14();//Pkw, keine Gefahrenbremsung, verschneiter Boden, Geschwindigkeit 50
    void testCase15();//Pkw, Gefahrenbremsung, trockener Boden, Geschwindigkeit 50
    void testCase21();//Panzer, trockener Boden, Geschwindigkeit 50
    void testCase22();//Panzer, trockener Boden, Geschwindigkeit 70
    void testCase23();//Panzer, nasser Boden, Geschwindigkeit 50
    void testCase24();//Panzer, verschneiter Boden, Geschwindigkeit 50
    void testCase31();//Zug, trockener Boden, Geschwindigkeit 50
    void testCase32();//Zug, trockener Boden, Geschwindigkeit 70
    void testCase33();//Zug, nasser Boden, Geschwindigkeit 50
    void testCase34();//Zug, verschneiter Boden, Geschwindigkeit 50
};

BremswegTest::BremswegTest()
{
}

void BremswegTest::testCase11()
{
    Bremsweg Pkw(1, 50, 1, "PkW");
    Pkw.BremswegBerechnen();
    double bremsstrecke = Pkw.BremswegAbfragen();
    QVERIFY2(bremsstrecke == 39.3, "Bremsweg stimmt nicht");
}

void BremswegTest::testCase12()
{
    Bremsweg Pkw(1, 70, 1, "PkW");
    Pkw.BremswegBerechnen();
    double bremsstrecke = Pkw.BremswegAbfragen();
    QVERIFY2(bremsstrecke == 65.3, "Bremsweg stimmt nicht");
}

void BremswegTest::testCase13()
{
    Bremsweg Pkw(1.1, 50, 1, "PkW");
    Pkw.BremswegBerechnen();
    double bremsstrecke = Pkw.BremswegAbfragen();
    QVERIFY2(bremsstrecke == 43.2, "Bremsweg stimmt nicht");
}

void BremswegTest::testCase14()
{
    Bremsweg Pkw(2.5, 50, 1, "PkW");
    Pkw.BremswegBerechnen();
    double bremsstrecke = Pkw.BremswegAbfragen();
    QVERIFY2(bremsstrecke == 98.2, "Bremsweg stimmt nicht");
}

void BremswegTest::testCase15()
{
    Bremsweg Pkw(1, 50, 2, "PkW");
    Pkw.BremswegBerechnen();
    double bremsstrecke = Pkw.BremswegAbfragen();
    QVERIFY2(bremsstrecke == 26.2, "Bremsweg stimmt nicht");
}

void BremswegTest::testCase21()
{
    Bremsweg Pkw(1, 50, 1, "Panzer");
    Pkw.BremswegBerechnen();
    double bremsstrecke = Pkw.BremswegAbfragen();
    QVERIFY2(bremsstrecke == 20.4, "Bremsweg stimmt nicht");
}

void BremswegTest::testCase22()
{
    Bremsweg Pkw(1, 70, 1, "Panzer");
    Pkw.BremswegBerechnen();
    double bremsstrecke = Pkw.BremswegAbfragen();
    QVERIFY2(bremsstrecke == 32.2, "Bremsweg stimmt nicht");
}

void BremswegTest::testCase23()
{
    Bremsweg Pkw(1.1, 50, 1, "Panzer");
    Pkw.BremswegBerechnen();
    double bremsstrecke = Pkw.BremswegAbfragen();
    QVERIFY2(bremsstrecke == 22.4, "Bremsweg stimmt nicht");
}

void BremswegTest::testCase24()
{
    Bremsweg Pkw(2.5, 50, 1, "Panzer");
    Pkw.BremswegBerechnen();
    double bremsstrecke = Pkw.BremswegAbfragen();
    QVERIFY2(bremsstrecke == 51, "Bremsweg stimmt nicht");
}

void BremswegTest::testCase31()
{
    Bremsweg Pkw(1, 50, 1, "Zug");
    Pkw.BremswegBerechnen();
    double bremsstrecke = Pkw.BremswegAbfragen();
    QVERIFY2(bremsstrecke == 68.5, "Bremsweg stimmt nicht");
}

void BremswegTest::testCase32()
{
    Bremsweg Pkw(1, 70, 1, "Zug");
    Pkw.BremswegBerechnen();
    double bremsstrecke = Pkw.BremswegAbfragen();
    QVERIFY2(bremsstrecke == 126.5, "Bremsweg stimmt nicht");
}

void BremswegTest::testCase33()
{
    Bremsweg Pkw(1.1, 50, 1, "Zug");
    Pkw.BremswegBerechnen();
    double bremsstrecke = Pkw.BremswegAbfragen();
    QVERIFY2(bremsstrecke == 75.4, "Bremsweg stimmt nicht");
}

void BremswegTest::testCase34()
{
    Bremsweg Pkw(2.5, 50, 1, "Zug");
    Pkw.BremswegBerechnen();
    double bremsstrecke = Pkw.BremswegAbfragen();
    QVERIFY2(bremsstrecke == 171.3, "Bremsweg stimmt nicht");
}


QTEST_APPLESS_MAIN(BremswegTest)

#include "tst_bremswegtest.moc"
