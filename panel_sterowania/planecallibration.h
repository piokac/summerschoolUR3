#ifndef PLANECALLIBRATION_H
#define PLANECALLIBRATION_H

#include <QObject>
#include"waypoint.h"
#include"UR3Intermediator.h"
#include"macierz.h"


class PlaneCallibration : public QObject
{
    Q_OBJECT
public:
    explicit PlaneCallibration(UR3Intermediator *_ur3, QObject *parent = nullptr);

    void selectPoints(QVector<double> &v_punkt);
    QVector<double> minus(QVector<double> p1, QVector<double> p2);
    double norm(QVector<double> p);
    QVector<double> div(QVector<double> p, double d);
    QVector<double> cross(QVector<double>p1, QVector<double> p2);
    QVector<double> calculateTransformation(QVector<double> p);
    QVector<QVector<double>> calculateTransformation(QVector<QVector<double>> p);
    void wypisz_wektor(QVector<double> v);

    QVector<double> getV_punkt1() const;
    void setV_punkt1(const QVector<double> &value);

    QVector<double> getV_punkt2() const;
    void setV_punkt2(const QVector<double> &value);

    QVector<double> getV_punkt3() const;
    void setV_punkt3(const QVector<double> &value);

    QVector<double> getV_x() const;

    QVector<double> getV_y() const;

    QVector<double> getV_z() const;

    QVector<double> getTrans() const;


    void setV_x(const QVector<double> &value);

    void setV_y(const QVector<double> &value);

    void setV_z(const QVector<double> &value);

    void setTrans(const QVector<double> &value);

signals:

private slots:
    newPose(QVector<double> x, char flag);

public slots:
    void run_callibration(WayPoint *w, UR3Intermediator *u);


private:
    QVector<double> v_x;
    QVector<double> v_y;
    QVector<double> v_z;
    QVector<double> trans;
    QVector<double> v_punkt1;
    QVector<double> v_punkt2;
    QVector<double> v_punkt3;
    Macierz *M;
    UR3Intermediator *ur3;
};

#endif // PLANECALLIBRATION_H
