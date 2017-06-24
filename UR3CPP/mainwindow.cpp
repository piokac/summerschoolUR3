#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ur3 = new UR3Intermediator();
    //connect(this->ur3, SIGNAL(newJointPos(QVector<double>)),this,SLOT(OnNewJointPos(QVector<double>)));
    connect(this->ur3, SIGNAL(newPoseTCP(QVector<double>,char)),this, SLOT(OnNewTCP(QVector<double>,char)));
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

void MainWindow::OnNewTCP(QVector<double> data, char c)
{
    switch(c){
    case 'p':
        this->ui->lineEditBase->setText(QString::number(data[0]));
        this->ui->lineEditShoulder->setText(QString::number(data[1]));
        this->ui->lineEditElbow->setText(QString::number(data[2]));
        this->ui->lineEditWrist1->setText(QString::number(data[3]));
        this->ui->lineEditWrist2->setText(QString::number(data[4]));
        this->ui->lineEditWrist3->setText(QString::number(data[5]));
        break;
    case 't':
        this->ui->lineEditX->setText(QString::number(data[0]));
        this->ui->lineEditY->setText(QString::number(data[1]));
        this->ui->lineEditZ->setText(QString::number(data[2]));
        this->ui->lineEditRX->setText(QString::number(data[3]));
        this->ui->lineEditRY->setText(QString::number(data[4]));
        this->ui->lineEditRZ->setText(QString::number(data[5]));
        break;
    }



}
