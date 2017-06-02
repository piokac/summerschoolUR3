#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myo = new cMYO(null, this);
    ui->gridLayout->addWidget(myo->getWidget());
}

MainWindow::~MainWindow()
{
    delete ui;
}
