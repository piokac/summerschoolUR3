#include "macierz.h"

Macierz::Macierz(QObject *parent) : QObject(parent)
{
   /* setUnitMatrix(invMatrix);
    setUnitMatrix(Matrix);*/
    setUnitMatrix(invMatrix);
    setUnitMatrix(Matrix);
}

QVector<QVector<double>> Macierz::setH(QVector<double> x, QVector<double> y, QVector<double> z, QVector<double> trans)
{
    x.push_back(0);
    y.push_back(0);
    z.push_back(0);
    trans.push_back(1);

    Matrix.clear();

    Matrix.push_back(x);
    Matrix.push_back(y);
    Matrix.push_back(z);
    Matrix.push_back(trans);

    return Matrix;
}

QVector<QVector<double> > Macierz::setInvH(QVector<double> x, QVector<double> y, QVector<double> z, QVector<double> trans)
{
    QVector<double>xtemp;
    QVector<double>ytemp;
    QVector<double>ztemp;
    QVector<QVector<double>>Rt;
    QVector<double>dRt;

    xtemp.push_back(x[0]);
    xtemp.push_back(y[0]);
    xtemp.push_back(z[0]);

    ytemp.push_back(x[1]);
    ytemp.push_back(y[1]);
    ytemp.push_back(z[1]);

    ztemp.push_back(x[2]);
    ztemp.push_back(y[2]);
    ztemp.push_back(z[2]);

    Rt.push_back(xtemp);
    Rt.push_back(ytemp);
    Rt.push_back(ztemp);

    for(int i=0;i<Rt[0].size();i++)
    {
        double temp=0;
        for(int j=0;j<Rt[0].size();j++)
        {
           // temp+=(-trans[j])*Rt[i][j];
            temp+= Rt[j][i]*(-trans[j]);
        }
        dRt.push_back(temp);
    }

    for(int i=0;i<Rt.size();i++)
    {
        Rt[i].push_back(0);
    }

    dRt.push_back(1);

    invMatrix.clear();

    for(int i=0;i<Rt.size();i++)
    {
        invMatrix.push_back(Rt[i]);
    }
    invMatrix.push_back(dRt);

    return invMatrix;
}

QVector<double> Macierz::mul(QVector<double> v2)
{
    QVector<double>wektor_wynikowy;

    if(Matrix.size()==v2.size())
    {
        qDebug()<<"ok";
        qDebug()<<"wymiar macierzy: "<<Matrix.size()<<"X"<<Matrix[0].size();
        qDebug()<<"wymiar wektora: "<<v2.size();
        for(int i=0;i<Matrix[0].size();i++)
        {
            double temp=0;
             for(int j=0;j<v2.size();j++)
             {
                 temp+=Matrix[j][i]*v2[j];

             }
             wektor_wynikowy.push_back(temp);
        }
        return wektor_wynikowy;
    }
    else
    {
        qDebug()<<"wewnetrzne wymiary macierzy nie zgadzaja sie";
        qDebug()<<"wymiar macierzy: "<<Matrix.size();
        qDebug()<<"wymiar wektora: "<<v2.size();
    }
}

QVector<double> Macierz::inv_mul(const QVector<double>& v2)
{
    QVector<double>wektor_wynikowy;

    if(invMatrix.size()==v2.size())
    {
        for(int i=0;i<invMatrix[0].size();i++)
        {
            double temp=0;
             for(int j=0;j<v2.size();j++)
             {
                 temp+=invMatrix[j][i]*v2[j];

             }
             wektor_wynikowy.push_back(temp);
        }
        return wektor_wynikowy;
    }
    else
    {
        qDebug()<<"wewnetrzne wymiary macierzy nie zgadzaja sie";
        qDebug()<<"wymiar macierzy: "<<invMatrix.size();
        qDebug()<<"wymiar wektora: "<<v2.size();
    }
}

QVector<QVector<double>> Macierz::mulM(QVector<QVector<double> > v2)
{
    QVector<QVector<double>>macierz_wynikowa;
   /* if(v1.size()==v2[0].size())
    {*/
        for(int i=0;i<Matrix[0].size();i++)
        {
            for(int k=0;k<v2.size();k++)
            {
                for(int j=0;j<v2[0].size();j++)
                {
                    macierz_wynikowa[i][k]+=Matrix[i][j]*v2[j][k];
                }
            }
        }
    //}
    /*else
    {
        qDebug()<<"wewnetrzne wymiary macierzy nie zgadzaja sie";
    }*/
        return macierz_wynikowa;
}

void Macierz::setUnitMatrix(QVector<QVector<double>> H)
{
    QVector<double>x;
    QVector<double>y;
    QVector<double>z;
    QVector<double>trans;

    x.push_back(1);
    x.push_back(0);
    x.push_back(0);
    x.push_back(0);

    x.push_back(0);
    x.push_back(1);
    x.push_back(0);
    x.push_back(0);

    x.push_back(0);
    x.push_back(0);
    x.push_back(1);
    x.push_back(0);

    x.push_back(0);
    x.push_back(0);
    x.push_back(0);
    x.push_back(1);

    H.clear();

    H.push_back(x);
    H.push_back(y);
    H.push_back(z);
    H.push_back(trans);
}

void Macierz::setMatrix(const QVector<QVector<double> > &value)
{
    Matrix = value;
}

QVector<QVector<double> > Macierz::getMatrix() const
{
    return Matrix;
}

QVector<QVector<double> > Macierz::getInvMatrix() const
{
    return invMatrix;
}

void Macierz::setInvMatrix(const QVector<QVector<double> > &value)
{
    invMatrix = value;
}
