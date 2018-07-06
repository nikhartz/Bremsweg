#include <QObject>

#ifndef LIBBREMSWEG_H
#define LIBBREMSWEG_H

class Bremsweg : public QObject
{
    Q_OBJECT

public:
    Bremsweg();
    void BremswegBerechnen();
    // Wertübergabe für Test
    // Idee und erläuterung siehe tst_bremswegtest.cpp
    double BremswegRueckgabe();
    double untergrundfaktorRueckgabe();
    double gefahrenbremsungRueckgabe();
    double bremsbeschleunigungRueckgabe();
    double reaktionswegRueckgabe();
    double bremszeitRueckgabe();

public slots:
    void GeschwindigkeitSetzen(double neueGeschwindigkeit);
    void UntergrundfaktorSetzen(double neuerUntergrundfaktor);
    void GefahrenbremsungSetzen (int Gefahrenbremsung);
    void FahrzeugSetzen (std::string neuesFahrzeug);

signals:
    void WertGeaendert();

private:
    double untergrundfaktor;
    double geschwindigkeit;
    double bremsweg;
    int gefahrenbremsung;
    std::string fahrzeug;
    double bremsbeschleunigung;
    double reaktionsweg;
    double bremszeit;

};

#endif // LIBBREMSWEG_H
