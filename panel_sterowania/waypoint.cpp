#include "waypoint.h"
#include "ui_waypoint.h"
#include<qDebug>
WayPoint::WayPoint(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WayPoint)
{
    ui->setupUi(this);
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(selectSettings(QVector<double>&)));
}

WayPoint::~WayPoint()
{
    delete ui;
}

double WayPoint::getWx() const
{
    qDebug()<<ui->lineEdit_Wx->text().toDouble();
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

void WayPoint::selectSettings(QVector<double> &v_punkt)
{
    v_punkt.push_back(ui->lineEdit_Wx->text().toDouble());
    v_punkt.push_back(ui->lineEdit_Wy->text().toDouble());
    v_punkt.push_back(ui->lineEdit_Wz->text().toDouble());
    v_punkt.push_back(ui->lineEdit_Wrx->text().toDouble());
    v_punkt.push_back(ui->lineEdit_Wry->text().toDouble());
    v_punkt.push_back(ui->lineEdit_Wrz->text().toDouble());
}

/*QVector<double> WayPoint::get_v_tcppose()
{
    QVector<double> v;
    v.push_back(getWx());
    v.push_back(getWy());
    v.push_back(getWz());
    v.push_back(getWrx());
    v.push_back(getWry());
    v.push_back(getWrz());
}*/


