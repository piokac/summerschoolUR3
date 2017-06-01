#ifndef KALIBRACJA_H
#define KALIBRACJA_H
#include<iostream>
#include<QObject>
#include"mainwindow.h"

struct punkt
{
    float x, y, z;
};
struct punktTCP
{
    float tab[6];/** pierwsze 3 to wspolrzedne x,y,z, kolejne to orientacja, w ktorej sa przetrzymywane katy.
                   */
};
class kalibracja
{
public:
    kalibracja();

protected:

    QVector<punkt> punkty;


public:
    void pobierz_punkt(); ///ma pobrac punkt i dodac go do vector<punkt> punkty
    virtual QVector<punkt> transformuj() = 0;
    virtual void kalibracja() = 0;

public slots:
void TCPpose(punktTCP punkt);
};

#endif // KALIBRACJA_H
