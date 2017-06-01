#ifndef CKALIBRACJA2D_H
#define CKALIBRACJA2D_H

#include <QObject>
#include "kalibracja.h"

struct punkt2D
    {
        float wspolrzedna_x;
        float wspolrzedna_y;
    };
class cKalibracja2D : public cKalibracja
{
public:
    kalibracja2D();


protected:
    void kalibruj(QVector<punkt> pkt);


public:
    void kalibruj();
     ///kalibruje punkty
    QVector<punktTCP> transformuj(QVector<punktTCP> wektor);
    /**
   transformuj dla ulatwienia zwraca caly wektor punktow juz przetworzonych zamiast pojedynczego punktu
   zwraca on pierwsze 3 punkty przetworzone - x,y,z oraz katy takie same, jakie dostal/
      */


    ~kalibracja2D();
private:
    punktTCP P0;///wspolrzedne robota
    punkt vx;
    punkt vz;
    /**
      vx oraz vz sa to wektory okreslajace wspolczynniki kalibracji
      */
};

#endif // CKALIBRACJA2D_H
