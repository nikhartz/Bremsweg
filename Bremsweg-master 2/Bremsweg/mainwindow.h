#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "libbremsweg.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonBremswegberechnen_clicked();

    void on_checkBoxGefahrenbremsung_stateChanged(int arg1);

    void on_comboBoxFahrzeug_currentIndexChanged(const QString &arg1);

    void on_comboBoxUntergrund_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    Bremsweg* bremsweg = new Bremsweg();
    /*
     * Einfuehrung aller möglichen Auftretenden Fehlermehldungen,
     * bei dem Benutzer darauf hingewiesen wird, alle Angaben zu vervollstaendigen
    */
    const char* ERROR_FAHRZEUG = "Bitte Fahrzeug auswählen";
    const char* ERROR_UNTERGRUND = "Bitte Untergrund auswählen";
    const char* ERROR_FAHRZEUGundUNTERGRUND = "Bitte Fahrzeug und Untergrund auswählen";
    const char* ERROR_GESCHWINDIGKEIT_NUMMER = "Bitte eine Zahl als Geschwindigkeit eingeben";
    const char* ERROR_GESCHWINDIGKEIT_INVALID = "Bitte eine gültige Geschwindigkeit eingeben (0 bis 250kmh)";
};

#endif // MAINWINDOW_H
