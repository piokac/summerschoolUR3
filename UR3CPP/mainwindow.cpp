#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ur3 = new UR3Intermediator();
}

MainWindow::~MainWindow()
{
    delete ui;
}
