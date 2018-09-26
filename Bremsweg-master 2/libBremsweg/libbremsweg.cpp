#include "libbremsweg.h"
/**
 * @brief Bremsweg::Bremsweg
 *        Standardkonstruktor für die Klasse Bremsweg
 * @param keine
 * @return keine
 */
Bremsweg::Bremsweg()
:untergrundfaktor(1.0), geschwindigkeit(0.0), bremsweg(0.0), gefahrenbremsung (1), fahrzeug("PkW")
{
}

/**
 * @brief Bremsweg::Bremsweg
 *        Konstruktor im Testprogramm verwendet
 * @param untergrundfaktor (double); Wert abhängig von dem Untergrund
 * @param geschwindigkeit (double);  Geschwindigkeit des Fahrzeugs
 * @param gefahrenbremsung (int); Wert der Notbremse
 * @param fahrzeug (string); Fahrzeugtyp
 */
Bremsweg::Bremsweg(double untergrundfaktor, double geschwindigkeit, int gefahrenbremsung, std::string fahrzeug)
    :untergrundfaktor(untergrundfaktor), geschwindigkeit(geschwindigkeit), gefahrenbremsung(gefahrenbremsung),fahrzeug(fahrzeug)
{
}

/**
 * @brief Bremsweg::GeschwindigkeitSetzen
 *        Ändert die Geschwindigkeit des Fahrzeugs
 * @param neueGeschwindigkeit (double); Neue Geschwindigkeit des Fahrzeugs
 */
void Bremsweg::GeschwindigkeitSetzen(double neueGeschwindigkeit)
{
    if (geschwindigkeit != neueGeschwindigkeit)
    {
        geschwindigkeit = neueGeschwindigkeit;
        emit WertGeaendert();
    }
}

/**
 * @brief Bremsweg::UntergrundfaktorSetzen
 *        Ändert den Faktor des Untergrunds
 * @param neuerUntergrundfaktor (double); Wert des neuen Untergrunds
 */
void Bremsweg::UntergrundfaktorSetzen(double neuerUntergrundfaktor)
{
    if (untergrundfaktor != neuerUntergrundfaktor)
    {
        untergrundfaktor = neuerUntergrundfaktor;
        emit WertGeaendert();
    }
}

/**
 * @brief Bremsweg::GefahrenbremsungSetzen
 *        Ändert den Wert der Notbremse
 * @param Gefahrenbremsung (int); Ändert den Wert der Notbremse
 */
void Bremsweg::GefahrenbremsungSetzen(int Gefahrenbremsung)
{
    if (gefahrenbremsung != Gefahrenbremsung)
    {
        gefahrenbremsung = Gefahrenbremsung;
        emit WertGeaendert();
    }
}

/**
 * @brief Bremsweg::FahrzeugSetzen
 *        Ändert den Fahrzeugtyp
 * @param neuesFahrzeug (string); Neuer Fahrzeugtyp
 */
void Bremsweg::FahrzeugSetzen(std::string neuesFahrzeug)
{
    if (fahrzeug != neuesFahrzeug)
    {
        fahrzeug = neuesFahrzeug;
        emit WertGeaendert();
    }
}

/**
 * @brief Bremsweg::BremswegBerechnen
 *        Berechnet den Bremsweg des Fahrzeugs, abhängig von den Benutzereinstellungen, die derzeit in der Klasse gespeichert sind
 */
void Bremsweg::BremswegBerechnen()
{
    double NORMFALLBESCHLEUNIGUNG = 9.80665;
    double Haftreibungszahl = 0.0;
    double bremsbeschleunigung = 0.0;
    double bremszeit = 0.0;
    double reaktionsweg = geschwindigkeit/3.6;
    if (fahrzeug == "PkW")
    {
        Haftreibungszahl = 0.8;
        bremsbeschleunigung = Haftreibungszahl * NORMFALLBESCHLEUNIGUNG;
        bremszeit = (geschwindigkeit/3.6)/bremsbeschleunigung;
        if (gefahrenbremsung == 2)
        {
            bremsweg = (round((reaktionsweg+0.5*bremsbeschleunigung*bremszeit*bremszeit)*untergrundfaktor*10))/10;
        }
        else
        {
            bremsweg = (round((reaktionsweg+0.5*bremsbeschleunigung*bremszeit*bremszeit)*untergrundfaktor*15))/10;
        }
    }
    else if (fahrzeug == "Panzer")
    {
        Haftreibungszahl = 1.51;
        bremsbeschleunigung = Haftreibungszahl * Normfallbeschleunigung;
        bremszeit = (geschwindigkeit/3.6)/bremsbeschleunigung;
        bremsweg = (round((reaktionsweg+0.5*bremsbeschleunigung*bremszeit*bremszeit)*untergrundfaktor*10))/10;
    }
    else if (fahrzeug == "Zug")
    {
        Haftreibungszahl = 0.18;
        bremsbeschleunigung = Haftreibungszahl * Normfallbeschleunigung;
        bremszeit = (geschwindigkeit/3.6)/bremsbeschleunigung;
        bremsweg = (round((reaktionsweg+0.5*bremsbeschleunigung*bremszeit*bremszeit)*untergrundfaktor*10))/10;
    }
}

/**
 * @brief Bremsweg::BremswegAbfragen
 *        Gibt den Bremsweg zurück
 * @return bremsweg (double); berechneter Bremsweg
 */
double Bremsweg::BremswegAbfragen() const
{
    return bremsweg;
}
