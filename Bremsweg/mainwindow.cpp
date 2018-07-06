#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "libbremsweg.h"
#include <QMessageBox>
#include <QComboBox>

int i = 0, j = 0;
bool StartupFahrzeug = true;
bool StartupUntergrund = true;
bool gueltigesFahrzeug = false;
bool gueltigerUntergrund = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Combobox Fahrzeug bevölkern
    ui->comboBoxFahrzeug->addItem("Fahrzeugauswahl");
    ui->comboBoxFahrzeug->addItem("PkW");
    ui->comboBoxFahrzeug->addItem("Zug");
    ui->comboBoxFahrzeug->addItem("Panzer");

    //Combobox Untergrund bevölkern
    ui->comboBoxUntergrund->addItem("Untergrundauswahl");
    ui->comboBoxUntergrund->addItem("trocken");
    ui->comboBoxUntergrund->addItem("nass");
    ui->comboBoxUntergrund->addItem("verschneit");

    connect(
                bremsweg, &Bremsweg::WertGeaendert,
                bremsweg, &Bremsweg::BremswegBerechnen);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete bremsweg;
    delete ERROR_FAHRZEUG;
    delete ERROR_GESCHWINDIGKEIT_NEGATIV;
    delete ERROR_GESCHWINDIGKEIT_NUMMER;
    delete ERROR_UNTERGRUND;
}


void MainWindow::on_pushButtonBremswegberechnen_clicked()
{
    bool ok = false;
    QString AusgabeBremsweg ="";
    QString EingabeGeschwindigkeit = ui->lineEditGeschwindigkeit->text();
    double Geschwindigkeit = EingabeGeschwindigkeit.toDouble(&ok);
    if (gueltigesFahrzeug == true && gueltigerUntergrund == true)
    {
        if (ok == true)
        {
            if (Geschwindigkeit > 0 && Geschwindigkeit <= 600)
            {
                this -> bremsweg -> GeschwindigkeitSetzen(Geschwindigkeit);
                double bremsweg = this ->bremsweg->BremswegAbfragen();
                AusgabeBremsweg = QString::number(bremsweg);
                ui -> lcdBremsweg -> display(AusgabeBremsweg);
            }
            else
            {
                AusgabeBremsweg = QString(ERROR_GESCHWINDIGKEIT_NEGATIV);
                ui -> lcdBremsweg -> display("ERROR");
                QMessageBox::information(this, "Achtung", AusgabeBremsweg);
            }
        }
        else
        {
            AusgabeBremsweg = QString(ERROR_GESCHWINDIGKEIT_NUMMER);
            ui->lcdBremsweg->display("ERROR");
            QMessageBox::information(this, "Achtung", AusgabeBremsweg);
        }
    }
    else if (gueltigesFahrzeug == true && gueltigerUntergrund != true)
    {
        AusgabeBremsweg = QString(ERROR_UNTERGRUND);
        ui->lcdBremsweg->display("ERROR");
        QMessageBox::information(this, "Achtung", AusgabeBremsweg);
    }
    else if (gueltigesFahrzeug != true && gueltigerUntergrund == true)
    {
        AusgabeBremsweg = QString(ERROR_FAHRZEUG);
        ui->lcdBremsweg->display("ERROR");
        QMessageBox::information(this, "Achtung", AusgabeBremsweg);
    }
    else
    {
        AusgabeBremsweg = QString(ERROR_FAHRZEUGundUNTERGRUND);
        ui->lcdBremsweg->display("ERROR");
        QMessageBox::information(this, "Achtung", AusgabeBremsweg);
    }
}

void MainWindow::on_checkBoxGefahrenbremsung_stateChanged(int Gefahrenbremsung)
{
    if (Gefahrenbremsung)
    {
        QMessageBox::information(this, "Achtung", "Die Gefahrenbremsung wurde aktiviert, wird jedoch nur beim Auto berücksichtigt!");
        this -> bremsweg -> GefahrenbremsungSetzen(2);
    }
    else
    {
        this -> bremsweg -> GefahrenbremsungSetzen(1);
    }
}


void MainWindow::on_comboBoxFahrzeug_currentIndexChanged(const QString &Fahrzeug)
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
        if (StartupFahrzeug != true)
        {
            gueltigesFahrzeug = false;
            QMessageBox::information(this, "Achtung", "Bitte ein gültiges Fahrzeug auswählen");
        }
    }
    StartupFahrzeug = false;
    if (fahrzeug != "")
    {
        this -> bremsweg -> FahrzeugSetzen(fahrzeug);
    }
}

void MainWindow::on_comboBoxUntergrund_currentIndexChanged(const QString &Untergrund)
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
        if (StartupUntergrund != true)
        {
            gueltigerUntergrund = false;
            QMessageBox::information(this, "Achtung", "Bitte einen gültigen Untergrund auswählen");
        }
    }
    StartupUntergrund = false;
    if (untergrundfaktor != 0)
    {
        this -> bremsweg -> UntergrundfaktorSetzen(untergrundfaktor);
    }
}
