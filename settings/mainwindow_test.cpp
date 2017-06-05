#include "mainwindow_test.h"
#include "ui_mainwindow_test.h"
#include <QDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),
    ui(new Ui::MainWindow), ustawienia(new Settings("settings.ini", this)), currentModule(this)
{
    ui->setupUi(this);

    connect(ui->actionUstawienia, SIGNAL(triggered(bool)), this, SLOT(showSettings())); //sygnal wlaczajacy okno ustawien
    connect(this, SIGNAL(currentModuleChanged(QObject*)), ustawienia, SLOT(moduleChanged(QObject*))); //sygnal przekazujacy informacje o zmianie aktualnego modułu

    ustawienia->read(this); //odczyt ustawien z pliku
    emit currentModuleChanged(currentModule);//sygnał o zmianie aktualnego modułu (POTRZEBNY W CONTROL PANELU)
}

MainWindow::~MainWindow()
{
    delete ui;
    ustawienia->serialize(this); //zapis ustawien do pliku
    delete ustawienia;
}

void MainWindow::showSettings()
{
    SettingsWindow *ustawieniaOkno = ustawienia->getWindow(); //pobranie wskaznika do okna ustawien
    ustawieniaOkno->exec(); //wyswietlenie modalnego okna dialogowego
}

double MainWindow::getZmiennaDouble() const
{
    return zmiennaDouble;
}

void MainWindow::setZmiennaDouble(double value)
{
    zmiennaDouble = value;
}

int MainWindow::getZmiennaInt() const
{
    return zmiennaInt;
}

void MainWindow::setZmiennaInt(int value)
{
    zmiennaInt = value;
}

bool MainWindow::getZmiennaBool() const
{
    return zmiennaBool;
}

void MainWindow::setZmiennaBool(bool value)
{
    zmiennaBool = value;
}

QObject *MainWindow::getCurrentModule() const
{
    return currentModule;
}

QString MainWindow::getIP() const
{
    return IP;
}

void MainWindow::setIP(const QString &value)
{
    IP = value;
}
