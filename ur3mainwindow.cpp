#include "ur3mainwindow.h"
#include "ui_ur3mainwindow.h"

UR3MainWindow::UR3MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UR3MainWindow)
{
    ui->setupUi(this);
}

UR3MainWindow::~UR3MainWindow()
{
    delete ui;
}
