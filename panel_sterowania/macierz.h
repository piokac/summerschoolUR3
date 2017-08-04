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
    QVector<double> mul( QVector<double> v2);
    QVector<QVector<double>> mulM( QVector<QVector<double>> v2);

    void setMatrix(const QVector<QVector<double> > &value);

    QVector<QVector<double> > getMatrix() const;

signals:


public slots:

private:
    QVector<QVector<double>>Matrix;

};

#endif // MACIERZ_H
