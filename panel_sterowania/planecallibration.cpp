#include "planecallibration.h"


PlaneCallibration::PlaneCallibration(UR3Intermediator* _ur3, QObject *parent) : QObject(parent), wp(new WayPoint), M(new Macierz)
{
    connect(_ur3,SIGNAL(newPoseTCP(QVector<double> ,char )), this,SLOT(newPose(QVector<double> ,char)));
    ur3=_ur3;


}
/*void PlaneCallibration::selectPoints(QVector<double> &v_punkt)
{
    v_punkt.push_back(ui->lineEdit_x->text().toDouble());
    v_punkt.push_back(ui->lineEdit_y->text().toDouble());
    v_punkt.push_back(ui->lineEdit_z->text().toDouble());
    v_punkt.push_back(ui->lineEdit_Rx->text().toDouble());
    v_punkt.push_back(ui->lineEdit_Ry->text().toDouble());
    v_punkt.push_back(ui->lineEdit_Rz->text().toDouble());
}*/

QVector<double> PlaneCallibration::calculateTransformation(QVector<double> p)
{
    M->mul(M->setH(getV_x(), getV_y(), getV_z(), getTrans()),p);
}

QVector<QVector<double> > PlaneCallibration::calculateTransformation(QVector<QVector<double> > p)
{
    QVector<QVector<double>> v_punkty;
    for(int i=0;i<p.size();i++)
    {
        v_punkty.push_back(M->mul(M->setH(getV_x(), getV_y(), getV_z(), getTrans()),p[i]));
    }
    return v_punkty;
}

void PlaneCallibration::wypisz_wektor(QVector<double> v)
{
    for(int i=0;i<v.size();i++)
    {
        qDebug()<<"  "<<i<<"  "<<v[i];
    }
}

QVector<double> PlaneCallibration::minus(QVector<double> p1, QVector<double> p2)
{
    QVector<double> p;
    for(int i=0;i<p1.size();i++)
    {
        p[i]=p1[i]-p2[i];
    }
    return p;
}

double PlaneCallibration::norm(QVector<double> p)
{
    double wynik=0;
    for(int i=0;i<p.size();i++)
    {
        wynik+=pow(p[i],2);
    }
    double n=sqrt(wynik);

    return n;
}

QVector<double> PlaneCallibration::div(QVector<double> p, double d)
{
    QVector<double> ptemp;
    for(int i=0;i<p.size();i++)
    {
        ptemp[i]=p[i]*1/d;
    }
    return ptemp;
}

QVector<double> PlaneCallibration::cross(QVector<double> p1, QVector<double> p2)
{
    QVector<double> p;
    p[0]=p1[1]*p2[2]-p1[2]*p2[1];
    p[1]=p1[2]*p2[0]-p1[0]*p2[2];
    p[2]=p1[0]*p2[1]-p1[1]*p2[0];
    return p;
}

PlaneCallibration::newPose(QVector<double> x, char flag)
{
    if(flag=='t')
    {
        //wp->setPose(x);
        wp->PushButtonData(x);
    }
}

QVector<double> PlaneCallibration::getV_punkt3() const
{
    return v_punkt3;
}

void PlaneCallibration::setV_punkt3(const QVector<double> &value)
{
    v_punkt3 = value;
}

QVector<double> PlaneCallibration::getV_punkt2() const
{
    return v_punkt2;
}

void PlaneCallibration::setV_punkt2(const QVector<double> &value)
{
    v_punkt2 = value;
}

QVector<double> PlaneCallibration::getV_punkt1() const
{
    return v_punkt1;
}

void PlaneCallibration::setV_punkt1(const QVector<double> &value)
{
    v_punkt1 = value;
}

void PlaneCallibration::run_callibration()
{
       //WayPoint dlg;
       qDebug()<<"222333";
       //connect to ur3
        wp->SetText("poczatek ukladu wspolrzednych");
           if(wp->exec() == QDialog::Accepted)
           {
               wp->SetText("punkt na osi oX");
               setV_punkt1(wp->getPose());
               //selectPoints(v_punkt1);
               //zappisac punkt

               //ustawic opis
               if(wp->exec() == QDialog::Accepted)
               {
                   wp->SetText("punkt na osi oY");
                   setV_punkt2(wp->getPose());
                   //selectPoints(v_punkt2);

                   if(wp->exec() == QDialog::Accepted)
                   {
                      wp->SetText("aktualna pozycja we wspolrzednych roboczych");
                      setV_punkt3(wp->getPose());
                       //selectPoints(v_punkt3);
                      if(wp->exec()==QDialog::Accepted)
                      {
                          setV_x(div(minus(getV_punkt2(),getV_punkt1()),norm(minus(getV_punkt2(),getV_punkt1()))));
                          setV_z(div(cross(minus(getV_punkt2(),getV_punkt1()),minus(getV_punkt3(),getV_punkt1())),norm(cross(minus(getV_punkt2(),getV_punkt1()),minus(getV_punkt3(),getV_punkt1())))));
                          setV_y(cross(getV_z(), getV_x()));
                          setTrans(getV_punkt1());
                          M->setMatrix(M->setH(getV_x(), getV_y(), getV_z(),getTrans()));
                      }
                   }
               }
           }
}

void PlaneCallibration::setTrans(const QVector<double> &value)
{
    trans = value;
}

void PlaneCallibration::setV_z(const QVector<double> &value)
{
    v_z = value;
}

void PlaneCallibration::setV_y(const QVector<double> &value)
{
    v_y = value;
}

void PlaneCallibration::setV_x(const QVector<double> &value)
{
    v_x = value;
}

QVector<double> PlaneCallibration::getTrans() const
{
    return trans;
}

QVector<double> PlaneCallibration::getV_x() const
{
    return v_x;
}

QVector<double> PlaneCallibration::getV_z() const
{
    return v_z;
}

QVector<double> PlaneCallibration::getV_y() const
{
    return v_y;
}

