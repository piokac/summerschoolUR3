#ifndef PLANECALLIBRATION_H
#define PLANECALLIBRATION_H

#include <QObject>
#include<waypoint.h>
#include "UR3Intermediator.h"

class PlaneCallibration : public QObject
{
    Q_OBJECT
public:
    explicit PlaneCallibration(QObject *parent = nullptr);
    WayPoint *wp;

    void selectPoints(QVector<double> &v_punkt);
    void calculateTransformation(QVector<double> punkt1, QVector<double> punkt2, QVector<double> punkt3);
    QVector<double> transform(QVector<double> p_robocze);


    QVector<double> v_punkt1;
    QVector<double> v_punkt2;
    QVector<double> v_punkt3;
signals:

public slots:
    void run_callibration();

private:
    UR3Intermediator* ur3;
};

#endif // PLANECALLIBRATION_H
