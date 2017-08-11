#ifndef PLANECALLIBRATION_H
#define PLANECALLIBRATION_H

#include <QObject>
#include"waypoint.h"
#include"UR3Intermediator.h"
#include"macierz.h"

/**
 * @brief The PlaneCallibration class - klasa wykorzystywana do przeprowadzania kalibracji
 */
class PlaneCallibration : public QObject
{
    Q_OBJECT
public:
    explicit PlaneCallibration(UR3Intermediator *_ur3, QObject *parent = nullptr);
    /**
     * @brief minus - wyznaczanie różnicy dwóch wektorów
     * @param p1
     * @param p2
     * @return
     */
    QVector<double> minus(QVector<double> p1, QVector<double> p2);
    /**
     * @brief norm - wyznaczanie modułu wektora
     * @param p
     * @return
     */
    double norm(QVector<double> p);
    /**
     * @brief div - wyznaczanie ilorazu wektora i skalara
     * @param p
     * @param d
     * @return
     */
    QVector<double> div(QVector<double> p, double d);
    /**
     * @brief cross - wyznaczanie iloczynu wektorowego dwóch wektorów
     * @param p1
     * @param p2
     * @return
     */
    QVector<double> cross(QVector<double>p1, QVector<double> p2);
    /**
     * @brief calculateTransformation - przeliczanie pozycji punktu ze współrzędnych lokalnych na współrzędne TCP
     * @param p
     * @return
     */
    QVector<double> calculateTransformation(const QVector<double>& p);
    /**
     * @brief calculateTransformation - przeliczanie pozycji zbioru punktów ze współrzędnych lokalnych na współrzędne TCP
     * @param p
     * @return
     */
    QVector<QVector<double>> calculateTransformation(QVector<QVector<double>> p);
    /**
     * @brief getV_punkt1
     * @return
     */
    QVector<double> getV_punkt1() const;
    /**
     * @brief setV_punkt1
     * @param value
     */
    void setV_punkt1(const QVector<double> &value);
    /**
     * @brief getV_punkt2
     * @return
     */
    QVector<double> getV_punkt2() const;
    /**
     * @brief setV_punkt2
     * @param value
     */
    void setV_punkt2(const QVector<double> &value);
    /**
     * @brief getV_punkt3
     * @return
     */
    QVector<double> getV_punkt3() const;
    /**
     * @brief setV_punkt3
     * @param value
     */
    void setV_punkt3(const QVector<double> &value);
    /**
     * @brief getV_x
     * @return
     */
    QVector<double> getV_x() const;
    /**
     * @brief getV_y
     * @return
     */
    QVector<double> getV_y() const;
    /**
     * @brief getV_z
     * @return
     */
    QVector<double> getV_z() const;
    /**
     * @brief getTrans
     * @return
     */
    QVector<double> getTrans() const;


    void setV_x(const QVector<double> &value);

    void setV_y(const QVector<double> &value);

    void setV_z(const QVector<double> &value);

    void setTrans(const QVector<double> &value);

signals:

public slots:
    /**
     * @brief run_callibration - procedura kalibracji
     * @param w
     * @param u
     */
    void run_callibration(WayPoint *w, UR3Intermediator *u);


private:
    QVector<double> v_x;/*!<wektor, który będzie pierwszą kolumną macierzy rotacji należącej blokowo do macierzy transformacji*/
    QVector<double> v_y;/*!<wektor, który będzie drugą kolumną macierzy rotacji należącej blokowo do macierzy transformacji*/
    QVector<double> v_z;/*!<wektor, który będzie trzecią kolumną macierzy rotacji należącej blokowo do macierzy transformacji*/
    QVector<double> trans;/*!<wektor translacji należący blokowo do macierzy transformacji*/
    QVector<double> v_punkt1;/*!<pierwszy punkt kalibracji*/
    QVector<double> v_punkt2;/*!<drugi punkt kalibracji*/
    QVector<double> v_punkt3;/*!<trzeci punkt kalibracji*/
    Macierz *M;
    UR3Intermediator *ur3;
};

#endif // PLANECALLIBRATION_H
