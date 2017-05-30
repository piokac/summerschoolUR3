#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controlpanel.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
ui->setupUi(this);
 controlpanel* test=new controlpanel;
setCentralWidget(test);


}

MainWindow::~MainWindow()
{
    delete ui;
}
