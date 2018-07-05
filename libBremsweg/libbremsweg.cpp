#include "libbremsweg.h"

Bremsweg::Bremsweg()
:untergrundfaktor(1.0), geschwindigkeit(0.0), fahrzeug("PkW"), bremsweg(0.0), gefahrenbremsung (1)
{
}

void Bremsweg::GeschwindigkeitSetzen(double neueGeschwindigkeit)
{
    if (geschwindigkeit != neueGeschwindigkeit)
    {
        geschwindigkeit = neueGeschwindigkeit;
        emit WertGeaendert();
    }
}

void Bremsweg::UntergrundfaktorSetzen(double neuerUntergrundfaktor)
{
    if (untergrundfaktor != neuerUntergrundfaktor)
    {
        untergrundfaktor = neuerUntergrundfaktor;
        emit WertGeaendert();
    }
}

void Bremsweg::GefahrenbremsungSetzen(int Gefahrenbremsung)
{
    if (gefahrenbremsung != Gefahrenbremsung)
    {
        gefahrenbremsung = Gefahrenbremsung;
        emit WertGeaendert();
    }
}

void Bremsweg::FahrzeugSetzen(std::string neuesFahrzeug)
{
    if (fahrzeug != neuesFahrzeug)
    {
        fahrzeug = neuesFahrzeug;
        emit WertGeaendert();
    }
}

void Bremsweg::BremswegBerechnen()
{
    if (fahrzeug == "PkW")
    {
        bremsweg = (((geschwindigkeit/10.0)*(geschwindigkeit/10.0))/gefahrenbremsung)*untergrundfaktor;
    }
    else if (fahrzeug == "Kettenfahrzeug")
    {
        bremsweg = -2;
    }
    else if (fahrzeug == "Zug")
    {
        bremsweg = -1;
    }
}

double Bremsweg::BremswegAbfragen() const
{
    return bremsweg;
}
