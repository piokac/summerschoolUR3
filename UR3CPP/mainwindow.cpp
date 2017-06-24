#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ur3 = new UR3Intermediator();
    connect(this->ur3,SIGNAL(newJointsPos(QVector<double>)),this,SLOT(OnNewJointPos(QVector<double>)));
    //connect(this->ur3,SIGNAL(newTCP(QVector<double>)),this,SLOT(OnNewTCP(QVector<double>)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnNewJointPos(QVector<double> pose)
{
    this->ui->lineEditBase->setText(QString::number(pose[0]));
    this->ui->lineEditShoulder->setText(QString::number(pose[1]));
    this->ui->lineEditElbow->setText(QString::number(pose[2]));
    this->ui->lineEditWrist1->setText(QString::number(pose[3]));
    this->ui->lineEditWrist2->setText(QString::number(pose[4]));
    this->ui->lineEditWrist3->setText(QString::number(pose[5]));
}

/*void MainWindow::OnNewTCP(QVector<double> tcp)
{
    this->ui->lineEditX->setText(QString::number(tcp[0]));
    this->ui->lineEditY->setText(QString::number(tcp[1]));
    this->ui->lineEditZ->setText(QString::number(tcp[2]));
    this->ui->lineEditRX->setText(QString::number(tcp[3]));
    this->ui->lineEditRY->setText(QString::number(tcp[4]));
    this->ui->lineEditRZ->setText(QString::number(tcp[5]));
}*/
