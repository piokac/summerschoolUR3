#include "ur3mainwindow.h"
#include "ui_ur3mainwindow.h"

UR3MainWindow::UR3MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UR3MainWindow)
{
    ui->setupUi(this);
    //odczyt ustawien
    ustawienia("settings");
    //    robot = new UR3Intermediator();
    //    Settings.read(robot);

    //    myo = new myo(robot);
    //    Settings.restore(myo);
    //    myo->setBinary(Settings.restoreBinary(myo));
}

UR3MainWindow::~UR3MainWindow()
{
    //    Settings.serialize(robot);
    //    Settings.serializeBinary(robot,robot->getBinary());
    delete ustawienia;
    delete ui;
}
