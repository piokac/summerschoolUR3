#include "macierz.h"

Macierz::Macierz(QObject *parent) : QObject(parent)
{

}

QVector<QVector<double>> Macierz::setH(QVector<double> x, QVector<double> y, QVector<double> z, QVector<double> trans)
{
    x.push_back(0);
    y.push_back(0);
    z.push_back(0);
    trans.push_back(1);

    QVector<QVector<double>> M;

    M.push_back(x);
    M.push_back(y);
    M.push_back(z);
    M.push_back(trans);

    return M;
}

QVector<double> Macierz::mul(QVector<QVector<double>> v1,QVector<double> v2)
{
    QVector<double>wektor_wynikowy;
   /* if(v1.size()==v2[0].size())
    {*/
        for(int i=0;i<v1[0].size();i++)
        {
             for(int j=0;j<v2.size();j++)
             {
                 wektor_wynikowy[i]+=v1[i][j]*v2[j];
             }
        }
    //}
    /*else
    {
        qDebug()<<"wewnetrzne wymiary macierzy nie zgadzaja sie";
    }*/
        return wektor_wynikowy;
}

QVector<QVector<double>> Macierz::mulM(QVector<QVector<double>> v1, QVector<QVector<double> > v2)
{
    QVector<QVector<double>>macierz_wynikowa;
   /* if(v1.size()==v2[0].size())
    {*/
        for(int i=0;i<v1[0].size();i++)
        {
            for(int k=0;k<v2.size();k++)
            {
                for(int j=0;j<v2[0].size();j++)
                {
                    macierz_wynikowa[i][k]+=v1[i][j]*v2[j][k];
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
