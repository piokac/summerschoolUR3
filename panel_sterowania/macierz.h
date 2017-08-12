#ifndef MACIERZ_H
#define MACIERZ_H

#include <QObject>
#include<QVector>
#include<QDebug>

/**
 * @brief The Macierz class - klasa przechowująca dane o macierzy transformacji
 */
class Macierz : public QObject
{
    Q_OBJECT
public:
    explicit Macierz(QObject *parent = nullptr);
    /**
     * @brief setH - ustawianie macierzy transformacji na podstawie macierzy rotacji i wektora translacji
     * @param x - pierwsza kolumna macierzy rotacji blokowo należącej do macierzy transformacji
     * @param y - druga kolumna macierzy rotacji blokowo należącej do macierzy transformacji
     * @param z - trzecia kolumna macierzy rotacji blokowo należącej do macierzy transformacji
     * @param trans - wektor translacji
     * @return  - zwraca macierz
     */
    QVector<QVector<double> >setH(QVector<double> x, QVector<double> y, QVector<double> z, QVector<double> trans);
    /**
     * @brief setInvH - ustawianie macierzy odwrotną transformacji
     * @param x - pierwsza kolumna macierzy rotacji blokowo należącej do macierzy transformacji
     * @param y - druga kolumna macierzy rotacji blokowo należącej do macierzy transformacji
     * @param z - trzecia kolumna macierzy rotacji blokowo należącej do macierzy transformacji
     * @param trans - wektor translacji
     * @return - zwraca macierz odwrotną
     */
    QVector<QVector<double>> setInvH(QVector<double> x, QVector<double> y, QVector<double> z, QVector<double> trans);
    /**
     * @brief mul - wyznaczanie iloczynu macierzy transformacji i wektora
     * @param v2
     * @return
     */
    QVector<double> mul( QVector<double> v2);
    /**
     * @brief inv_mul - wyznaczanie iloczynu macierzy odwrotnej transformacji i wektora
     * @param v
     * @return
     */
    QVector<double> inv_mul(const QVector<double>& v);
    /**
     * @brief mulM - wyznaczanie iloczynu macierzy transformacji i innej macierzy (zbioru punktów)
     * @param v2
     * @return
     */
    QVector<QVector<double>> mulM( QVector<QVector<double>> v2);
    /**
     * @brief setUnitMatrix - ustawianie macierzy jako jednostkowej
     * @param H
     */
    void setUnitMatrix(QVector<QVector<double>> H);

    void setMatrix(const QVector<QVector<double> > &value);   
    QVector<QVector<double> > getMatrix() const;

    QVector<QVector<double> > getInvMatrix() const;
    void setInvMatrix(const QVector<QVector<double> > &value);

signals:

public slots:

private:
    QVector<QVector<double>>Matrix;/*!<macierz transformacji*/
    QVector<QVector<double>>invMatrix;/*!<macierz odwrotna transformacji*/
};

#endif // MACIERZ_H
