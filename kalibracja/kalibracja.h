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
    virtual QVector<punktTCP> transformuj(QVector<punkt> wektor) = 0;
    /**
     * @brief transformuj() zwraca wektor punktow TCP, a oczekuje wektora punktow, poniewaz 3 ostatnie argumenty
     * punktTCP nie ulegaly zmianie - katy ustawienia. ma to skutek taki, ze ostatnia czesc manipulatora
     * za kazdym razem bd ustawiona pod tym samym kontem.
     */
    virtual void kalibracja() = 0;

public slots:
void TCPpose(punktTCP punkt);
};

#endif // KALIBRACJA_H
