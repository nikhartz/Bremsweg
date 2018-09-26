#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "libbremsweg.h"
#include <QMessageBox>
#include <QComboBox>

bool StartupFahrzeug = true; //verhindert das beim starten des Programms direkt eine Fehlermeldung kommt
bool StartupUntergrund = true; //verhindert das beim starten des Programms direkt eine Fehlermeldung kommt
bool gueltigesFahrzeug = false;
bool gueltigerUntergrund = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->comboBoxFahrzeug->addItem("Fahrzeugauswahl");
    ui->comboBoxFahrzeug->addItem("PkW");
    ui->comboBoxFahrzeug->addItem("Zug");
    ui->comboBoxFahrzeug->addItem("Panzer");

    ui->comboBoxUntergrund->addItem("Untergrundauswahl");
    ui->comboBoxUntergrund->addItem("trocken");
    ui->comboBoxUntergrund->addItem("nass");
    ui->comboBoxUntergrund->addItem("verschneit");

    connect(bremsweg, &Bremsweg::WertGeaendert,
        bremsweg, &Bremsweg::BremswegBerechnen);//bei einer Wertänderung wird automatisch der neue Bremsweg berechnet
}

MainWindow::~MainWindow()
{
    delete ui;
    delete bremsweg;
    delete ERROR_FAHRZEUG;
    delete ERROR_GESCHWINDIGKEIT_INVALID;
    delete ERROR_GESCHWINDIGKEIT_NUMMER;
    delete ERROR_UNTERGRUND;
}

/**
 * @brief MainWindow::on_pushButtonBremswegberechnen_clicked
 *       Wenn der Button "Bremsweg berechnen" angeklickt wird, berechnet das Programm den Bremsweg des Fahrzeuges mit der gegebenen Art des Untergrundes und Geschwindigkeit
 * @param bremsweg(double); Aktuell berechneter Bremsweg, je nach Klasse
 * @return AusgabeBremsweg (string); Halteabstand je nach Klasse zur Anzeige im LCD-Display
 */

void MainWindow::on_pushButtonBremswegberechnen_clicked()//"Bremsweg berechnen" geklicked
{
    bool ok = false;
    QString AusgabeBremsweg ="";
    QString EingabeGeschwindigkeit = ui->lineEditGeschwindigkeit->text();
    double Geschwindigkeit = EingabeGeschwindigkeit.toDouble(&ok);
    if (gueltigesFahrzeug == true && gueltigerUntergrund == true) //Abfrage auf gültigen Untergrund und gültiges Fahrzeug
    {
        if (ok == true) //Umwandlung von ok nach Double
        {
            if (Geschwindigkeit > 0 && Geschwindigkeit <= 250)// Einhalten einer gültigen Geschwindigkeit
            {
                this -> bremsweg -> GeschwindigkeitSetzen(Geschwindigkeit);
                double bremsweg = this ->bremsweg->BremswegAbfragen();
                AusgabeBremsweg = QString::number(bremsweg);
                ui -> lcdBremsweg -> display(AusgabeBremsweg);
            }
            else //Geschwindigkeit nicht negativ oder größer als 250 km/h
            {
                AusgabeBremsweg = QString(ERROR_GESCHWINDIGKEIT_INVALID);
                ui -> lcdBremsweg -> display("ERROR");
                QMessageBox::information(this, "Achtung", AusgabeBremsweg);
            }
        }
        else //keine Zahl bei Geschwindigkeitseingabe
        {
            AusgabeBremsweg = QString(ERROR_GESCHWINDIGKEIT_NUMMER);
            ui->lcdBremsweg->display("ERROR");
            QMessageBox::information(this, "Achtung", AusgabeBremsweg);
        }
    }
    else if (gueltigesFahrzeug == true && gueltigerUntergrund != true) //Verhindert dass nicht ohne gueltigen Untergrund gerechnet wird
    {
        AusgabeBremsweg = QString(ERROR_UNTERGRUND);
        ui->lcdBremsweg->display("ERROR");
        QMessageBox::information(this, "Achtung", AusgabeBremsweg);
    }
    else if (gueltigesFahrzeug != true && gueltigerUntergrund == true) // //Verhindert dass nicht ohne gueltiges Farhzeug gerechnet wird
    {
        AusgabeBremsweg = QString(ERROR_FAHRZEUG);
        ui->lcdBremsweg->display("ERROR");
        QMessageBox::information(this, "Achtung", AusgabeBremsweg);
    }
    else //kein Fahrzeug und kein Untergrund ausgewählt, Fehlerausgabe
    {
        AusgabeBremsweg = QString(ERROR_FAHRZEUGundUNTERGRUND);
        ui->lcdBremsweg->display("ERROR");
        QMessageBox::information(this, "Achtung", AusgabeBremsweg);
    }
}

/**
 * @brief MainWindow::on_checkBoxGefahrenbremsung_stateChanged
 *        Checkbox zum Aktivieren der Notbremse, wenn das Fahrzeug ein Auto ist, ist die Notbremse aktiviert
 * @param Gefahrenbremsung (int); Aktueller Status der Checkbox
 * @return GefahrenbremsungSetzen (int); Der Rückgabewert wurde an die Klasse zurückgegeben, abhängig vom Status der Checkbox
 */
void MainWindow::on_checkBoxGefahrenbremsung_stateChanged(int Gefahrenbremsung) //Zustand der Gefahrenbremsung geändert
{
    if (Gefahrenbremsung) //Haken bei Gefahrenbremsung gesetzt
    {
        QMessageBox::information(this, "Achtung", "Die Gefahrenbremsung wurde aktiviert, wird jedoch nur beim Auto berücksichtigt!");
        this -> bremsweg -> GefahrenbremsungSetzen(2);
    }
    else //Haken bei Gefahrenbremsung entfernt
    {
        this -> bremsweg -> GefahrenbremsungSetzen(1);
    }
}

/**
 * @brief MainWindow::on_comboBoxFahrzeug_currentIndexChanged
 *        Combobox, um den Fahrzeugtyp zu ändern
 * @param Fahrzeug (string); Der String der momentan in der Combobox angezeigt wird
 * @param gueltigesFahrzeug (bool); Globale Variable, um einen Fehler beim Starten des Programms zu verhindern
 * @return fahrzeug (string); String wird an Klasse zurückgegeben, abhängig vom ausgewaehltem Fahrzeug
 */
void MainWindow::on_comboBoxFahrzeug_currentIndexChanged(const QString &Fahrzeug) //Fahrzeugauswahl geändert
{
    std::string fahrzeug = "";
    if (Fahrzeug == "Zug")
    {
        gueltigesFahrzeug = true;
        fahrzeug = "Zug";
    }
    else if (Fahrzeug == "PkW")
    {
        gueltigesFahrzeug = true;
        fahrzeug = "PkW";
    }
    else if (Fahrzeug == "Panzer")
    {
        gueltigesFahrzeug = true;
        fahrzeug = "Panzer";
    }
    else
    {
        if (StartupFahrzeug != true) //Wenn man den Eintrag "Fahrzeugauswahl" erneut auswaehlt kommt eine Fehlermeldung, jedoch nicht beim Start
        {
            gueltigesFahrzeug = false;
            QMessageBox::information(this, "Achtung", "Bitte ein gültiges Fahrzeug auswählen");
        }
    }
    StartupFahrzeug = false;//nach dem ersten Mal wechseln wird der "Startmodus" verlassen, ein wechsel auf "Fahrzeugauswahl" bringt jetzt eine Fehlermeldung
    if (fahrzeug != "")
    {
        this -> bremsweg -> FahrzeugSetzen(fahrzeug);
    }
}

/**
 * @brief MainWindow::on_comboBoxUntergrund_currentIndexChanged
 *        Combobox, um den Untergrund zu verändern
 * @param Untergrund (string); Der String der momentan in der Combobox angezeigt wird
 * @param gueltigerUntergrund (bool); Globale Variable, um einen Fehler beim Starten des Programms zu verhindern
 * @return untergrundfaktor (double); Rückgabewert an die Klasse, abhängig vom ausgewählten Untergrund
 */
void MainWindow::on_comboBoxUntergrund_currentIndexChanged(const QString &Untergrund)//Untergrund wird je nach Eingabe der ComboBox geaendert
{
    double untergrundfaktor = 0.0;
    if (Untergrund == "trocken")
    {
        gueltigerUntergrund = true;
         untergrundfaktor = 1;
    }
    else if (Untergrund == "nass")
    {
        gueltigerUntergrund = true;
        untergrundfaktor = 1.1;
    }
    else if (Untergrund == "verschneit")
    {
        gueltigerUntergrund = true;
        untergrundfaktor = 2.5;
    }
    else
    {
        if (StartupUntergrund != true)//Wenn man den Eintrag "Untergrundauswahl" erneut auswaehlt kommt eine Fehlermeldung, jedoch nicht beim Start
        {
            gueltigerUntergrund = false;
            QMessageBox::information(this, "Achtung", "Bitte einen gültigen Untergrund auswählen");
        }
    }
    StartupUntergrund = false;//nach dem ersten Wechsel wird der "Startmodus" verlassen, ein Wechsel auf "Untergrundauswahl" bringt jetzt eine Fehlermeldung
    if (untergrundfaktor != 0)
    {
        this -> bremsweg -> UntergrundfaktorSetzen(untergrundfaktor);
    }
}
