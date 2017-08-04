#include "macierz.h"

Macierz::Macierz(QObject *parent) : QObject(parent)
{
    setH({1,0,0},{0,1,0},{0,0,1},{0,0,0});
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

QVector<double> Macierz::mul(QVector<double> v2)
{
    QVector<double>wektor_wynikowy;
    if(Matrix.size()==v2.size())
    {
        qDebug()<<"ok";
        for(int i=0;i<Matrix[0].size();i++)
        {
             for(int j=0;j<v2.size();j++)
             {
                 wektor_wynikowy[i]+=Matrix[i][j]*v2[j];
             }
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

void Macierz::setMatrix(const QVector<QVector<double> > &value)
{
    Matrix = value;
}

QVector<QVector<double> > Macierz::getMatrix() const
{
    return Matrix;
}
