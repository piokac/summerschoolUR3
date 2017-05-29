#ifndef POLYLINE2UR3_H
#define POLYLINE2UR3_H

#include <QObject>
#include "mainwindow.h"

class Polyline2UR3 : public QObject
{
    Q_OBJECT
public:
    explicit Polyline2UR3(QObject *parent = 0);
    void SendDataToUR3();
    void Calibrate();


signals:

public slots:
};

#endif // POLYLINE2UR3_H
