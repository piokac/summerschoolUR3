#include "planecallibration.h"

PlaneCallibration::PlaneCallibration(QObject *parent) : QObject(parent)
{

}

void PlaneCallibration::selectPoints(QVector<double> &v_punkt)
{
    /*v_punkt.push_back(ui->lineEdit_x->text().toDouble());
    v_punkt.push_back(ui->lineEdit_y->text().toDouble());
    v_punkt.push_back(ui->lineEdit_z->text().toDouble());
    v_punkt.push_back(ui->lineEdit_Rx->text().toDouble());
    v_punkt.push_back(ui->lineEdit_Ry->text().toDouble());
    v_punkt.push_back(ui->lineEdit_Rz->text().toDouble());*/
}

void PlaneCallibration::calculateTransformation(QVector<double> punkt1, QVector<double> punkt2, QVector<double> punkt3)
{

}

QVector<double> PlaneCallibration::transform(QVector<double> p_robocze)
{

}

void PlaneCallibration::run_callibration()
{
       /*WayPoint dlg;
       //connect to ur3

       if(ur3->ConnectToRobot())
       {
           qDebug()<<"eeee";
           if(dlg.exec() == QDialog::Accepted)
           {
               //selectPoints(v_punkt1);
               //zappisac punkt

               //ui->labelpl->setText("poczatek ukladu wspolrzednych");
               //ustawic opis
               if(dlg.exec() == QDialog::Accepted)
               {
                   //selectPoints(v_punkt2);

                   if(dlg.exec() == QDialog::Accepted)
                   {
                       //selectPoints(v_punkt3);
                   }
               }
           }
       }*/
}
