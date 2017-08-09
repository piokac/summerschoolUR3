#ifndef MACIERZ_H
#define MACIERZ_H

#include <QObject>
#include<QVector>
#include<QDebug>


class Macierz : public QObject
{
    Q_OBJECT
public:
    explicit Macierz(QObject *parent = nullptr);
    QVector<QVector<double> >setH(QVector<double> x, QVector<double> y, QVector<double> z, QVector<double> trans);
    QVector<QVector<double>> setInvH(QVector<double> x, QVector<double> y, QVector<double> z, QVector<double> trans);
    QVector<double> mul( QVector<double> v2);
    QVector<double> inv_mul(QVector<double> v);
    QVector<QVector<double>> mulM( QVector<QVector<double>> v2);

    void setUnitMatrix(QVector<QVector<double>> H,QVector<double> x, QVector<double> y, QVector<double> z, QVector<double> trans);

    void setMatrix(const QVector<QVector<double> > &value);
    QVector<QVector<double> > getMatrix() const;

    QVector<QVector<double> > getInvMatrix() const;
    void setInvMatrix(const QVector<QVector<double> > &value);

signals:


public slots:

private:
    QVector<QVector<double>>Matrix;
    QVector<QVector<double>>invMatrix;

};

#endif // MACIERZ_H
