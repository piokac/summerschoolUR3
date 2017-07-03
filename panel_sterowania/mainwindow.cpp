#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),settings(new Settings("settings.ini", this)),  ur3(new UR3Intermediator),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionUstawienia_okna,SIGNAL(triggered(bool)),this,SLOT(showConfigWindow()));
    settings->read(this);
    settings->read(ur3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showConfigWindow()
{
    settings->moduleChanged(ur3);
    SettingsWindow *ustawieniaOkno = settings->getWindow(); //pobranie wskaznika do okna ustawien
    ustawieniaOkno->exec(); //wyswietlenie modalnego okna dialogowego
}

QString MainWindow::getPole2() const
{
    return pole2;
}

void MainWindow::setPole2(const QString &value)
{
    pole2 = value;
}

int MainWindow::getPole1() const
{
    return pole1;
}

void MainWindow::setPole1(int value)
{
    pole1 = value;
}
