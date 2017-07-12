#include "waypoint.h"
#include "ui_waypoint.h"
#include<qDebug>
WayPoint::WayPoint(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WayPoint)
{
    ui->setupUi(this);

}

WayPoint::~WayPoint()
{
    delete ui;
}

double WayPoint::getWx() const
{
    return  ui->lineEdit_Wx->text().toDouble();
}

void WayPoint::setWx(double value)
{
    value = ui->lineEdit_Wx->text().toDouble();
    Wx = value;
}

double WayPoint::getWy() const
{
    return  ui->lineEdit_Wy->text().toDouble();
}

void WayPoint::setWy(double value)
{
    value = ui->lineEdit_Wy->text().toDouble();
    Wy = value;
}

double WayPoint::getWz() const
{

    return  ui->lineEdit_Wz->text().toDouble();
}

void WayPoint::setWz(double value)
{
    value = ui->lineEdit_Wz->text().toDouble();
    Wz = value;
}

double WayPoint::getWrx() const
{

    return  ui->lineEdit_Wrx->text().toDouble();
}

void WayPoint::setWrx(double value)
{
    value = ui->lineEdit_Wrx->text().toDouble();
    Wrx = value;
}

double WayPoint::getWry() const
{

    return  ui->lineEdit_Wry->text().toDouble();
}

void WayPoint::setWry(double value)
{
    value = ui->lineEdit_Wry->text().toDouble();
    Wry = value;
}

double WayPoint::getWrz() const
{

    return  ui->lineEdit_Wrz->text().toDouble();
}

void WayPoint::setWrz(double value)
{
    value = ui->lineEdit_Wrz->text().toDouble();
    Wrz = value;
}

double WayPoint::getA() const
{

    return  ui->lineEdit_Wa->text().toDouble();
}

void WayPoint::setA(double value)
{
    value = ui->lineEdit_Wa->text().toDouble();
    a = value;
}

double WayPoint::getV() const
{
    return  ui->lineEdit_Wv->text().toDouble();
}

void WayPoint::setV(double value)
{

    value = ui->lineEdit_Wv->text().toDouble();
    V = value;
}

void WayPoint::PushButtonData(QVector<double> data)
{
    if (flaga == 1)
    {
        this->ui->lineEdit_Wx->setText(QString::number(data[0]));
        this->ui->lineEdit_Wy->setText(QString::number(data[1]));
        this->ui->lineEdit_Wz->setText(QString::number(data[2]));
        this->ui->lineEdit_Wrx->setText(QString::number(data[3]));
        this->ui->lineEdit_Wry->setText(QString::number(data[4]));
        this->ui->lineEdit_Wrz->setText(QString::number(data[5]));
        flaga = 0;
    }
}

void WayPoint::on_pushButton_Ap_pressed()
{
    flaga = 1;


}
