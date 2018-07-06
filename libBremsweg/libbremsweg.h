#include <QObject>

#ifndef LIBBREMSWEG_H
#define LIBBREMSWEG_H

class Bremsweg : public QObject
{
    Q_OBJECT

public:
    Bremsweg();
    double BremswegAbfragen() const;
    void BremswegBerechnen();
    std::string fahrzeug;
    double geschwindigkeit;

public slots:
    void GeschwindigkeitSetzen(double neueGeschwindigkeit);
    void UntergrundfaktorSetzen(double neuerUntergrundfaktor);
    void GefahrenbremsungSetzen (int Gefahrenbremsung);
    void FahrzeugSetzen (std::string neuesFahrzeug);

signals:
    void WertGeaendert();

private:
    double untergrundfaktor;
    //double geschwindigkeit;
    double bremsweg;
    int gefahrenbremsung;
    //std::string fahrzeug;
    double bremsbeschleunigung;
    double reaktionsweg;
    double bremszeit;

};

#endif // LIBBREMSWEG_H
