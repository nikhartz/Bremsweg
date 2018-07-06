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
// Idee war alles vorzugeben und dann aus normaler Bremsung und
// Gefahrenbremsung das Verältnis 1.5 rauszubekommen dann muss
// rechnung und einlesen stimmen
// variablenübergabe bekomm ich net hin dachte an Pointer.... voll verwirrender rotz
// um auf private variablen der class Bremsweg zuzugreifen
// hab ich die "Rueckgabe" funktionen eingeführt
{
    double untergrund = 1.0;
    char fahrzeug = 'PkW';
    double* geschwindigkeit = 60.0;
    geschwindigkeit = Bremsweg.BremswegRueckgabe();
    double gefahrenbremsungaus = 2.0;
    double gefahrenbremsungein = 1.0;
    double Bremswegnormal = Bremsweg.BremswegBerechnen();
    double Bremsweggefahr = 3 ;
    QVERIFY2(1.5 , )


}

QTEST_APPLESS_MAIN(BremswegTest)

#include "tst_bremswegtest.moc"
