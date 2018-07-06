using namespace std;
#include "libbremsweg.h"

double Normfallbeschleunigung = 9.80665;
double Haftreibungszahl = 0.0;

//bremsbeschleunigung,reaktionsweg  und bremszeit in class eingefügt um testcases einfacher zu machen

Bremsweg::Bremsweg()
:untergrundfaktor(1.0), geschwindigkeit(0.0), bremsweg(0.0), gefahrenbremsung (1),
 fahrzeug("PkW"),bremsbeschleunigung(0.0), reaktionsweg(0.0), bremszeit(0.0)
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

void Bremsweg::FahrzeugSetzen(string neuesFahrzeug)
{
    if (fahrzeug != neuesFahrzeug)
    {
        fahrzeug = neuesFahrzeug;
        emit WertGeaendert();
    }
}

void Bremsweg::BremswegBerechnen()
{
    reaktionsweg = geschwindigkeit/10*3;
    bremsbeschleunigung = Haftreibungszahl * Normfallbeschleunigung;
    bremszeit = (geschwindigkeit/3.6)/bremsbeschleunigung;

    if (fahrzeug == "PkW")
    {
        Haftreibungszahl = 0.8;
        double bremsbeschleunigung = Haftreibungszahl * Normfallbeschleunigung;
        double bremszeit = (geschwindigkeit/3.6)/bremsbeschleunigung;
        if (gefahrenbremsung == 2)
        {
            bremsweg = int((reaktionsweg+0.5*bremsbeschleunigung*bremszeit*bremszeit)*untergrundfaktor*100.0+0.5)/100.0;
        }
        else
        {
            bremsweg = int(((reaktionsweg+0.5*bremsbeschleunigung*bremszeit*bremszeit)*untergrundfaktor*1.5)*100.0+0.5)/100.0;
            //bremsweg = (round(((reaktionsweg+0.5*bremsbeschleunigung*bremszeit*bremszeit)*untergrundfaktor*1.5)*10))/10;
            //round wird bei mir als 'undeclared identifier' gewertet, deswegen klassisches Casten
        }
    }
    else if (fahrzeug == "Panzer")
    {
        Haftreibungszahl = 1.51;
        bremsweg = int(((reaktionsweg+0.5*bremsbeschleunigung*bremszeit*bremszeit)*untergrundfaktor*1.5)*100.0+0.5)/100.0;
    }
    else if (fahrzeug == "Zug")
    {
        Haftreibungszahl = 0.18;
        bremsweg = int(((reaktionsweg+0.5*bremsbeschleunigung*bremszeit*bremszeit)*untergrundfaktor*1.5)*100.0+0.5)/100.0;
    }
}

double Bremsweg::BremswegRueckgabe()
{
    return bremsweg;
}

double Bremsweg::untergrundfaktorRueckgabe()
{
    return untergrundfaktor;
}

double Bremsweg::gefahrenbremsungRueckgabe()
{
    return gefahrenbremsung;
}

double Bremsweg::bremsbeschleunigungRueckgabe()
{
    return bremsbeschleunigung ;
}

double Bremsweg::reaktionswegRueckgabe()
{
    return reaktionsweg;
}

double Bremsweg::bremszeitRueckgabe()
{
    return bremszeit;
}

