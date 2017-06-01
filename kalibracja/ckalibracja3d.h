#ifndef CKALIBRACJA3D_H
#define CKALIBRACJA3D_H

#include <QObject>
#include"kalibracja.h"

class cKalibracja3d: public kalibracja
{
public:
    kalibracja3D();


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


    ~kalibracja3D();
private:
    punktTCP P0;///wspolrzedne robota
    punkt vx;
    punkt vy;
    punkt vz;
    /**
      vx oraz vz sa to wektory okreslajace wspolczynniki kalibracji
      */
};

#endif // CKALIBRACJA3D_H
