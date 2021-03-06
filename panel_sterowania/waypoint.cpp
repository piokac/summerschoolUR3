
#include "waypoint.h"
#include "ui_waypoint.h"
#include<qDebug>
WayPoint::WayPoint(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WayPoint), M(new Macierz), plFlag(0),flaga(0)
{
    ui->setupUi(this);
    //connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(selectSettings(QVector<double>&)));
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



void WayPoint::PushButtonDataCC(QVector<double> data)
{
    if(plFlag==1)
    {
   
      QVector<double> _data2;
      QVector<double> configuration_data;
      _data2.push_back(data[0]);
      _data2.push_back(data[1]);
      _data2.push_back(data[2]);
      _data2.push_back(1);

      //configuration_data=M->mul(_data2);
      configuration_data=M->inv_mul(_data2);

      this->ui->lineEdit_Wx->setText(QString::number(configuration_data[0]));
      this->ui->lineEdit_Wy->setText(QString::number(configuration_data[1]));
      this->ui->lineEdit_Wz->setText(QString::number(configuration_data[2]));

      qDebug()<<"kalibracja udana!";
      plFlag = 0;
    }
}

QVector<double> WayPoint::getPose()
{
    QVector<double> v_punkt;
    v_punkt.push_back(ui->lineEdit_Wx->text().toDouble());
    v_punkt.push_back(ui->lineEdit_Wy->text().toDouble());
    v_punkt.push_back(ui->lineEdit_Wz->text().toDouble());
    v_punkt.push_back(ui->lineEdit_Wrx->text().toDouble());
    v_punkt.push_back(ui->lineEdit_Wry->text().toDouble());
    v_punkt.push_back(ui->lineEdit_Wrz->text().toDouble());
    return v_punkt;
}

/*void WayPoint::setPose(QVector<double> v)
{
    flaga = 1;
    PushButtonData(v);
}*/

void WayPoint::SetText(QString text)
{
    ui->label_description->setText(text);
}

void WayPoint::setTransformation(QVector<QVector<double> > v)
{
    M->setMatrix(v);
}

QVector<QVector<double> > WayPoint::getTransformation()
{
    return M->getMatrix();
}

void WayPoint::setInvTransformation(QVector<QVector<double> > v)
{
    M->setInvMatrix(v);
}

void WayPoint::on_pushButton_Ap_pressed()
{
    qDebug()<<"void WayPoint::on_pushButton_Ap_pressed()";
    flaga = 1;

}

void WayPoint::on_pushButton_cc_clicked()
{
    qDebug()<<"void WayPoint::on_pushButton_cc_clicked()";
    plFlag = 1;

}

void WayPoint::on_pushButton_Ap_clicked()
{

}

void WayPoint::on_pushButton_cc_pressed()
{

}
