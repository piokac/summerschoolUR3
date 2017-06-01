#ifndef CKALIBRACJA1D_H
#define CKALIBRACJA1D_H

#include <QObject>
#include "kalibracja.h"

class cKalibracja1D : public kalibracja
{
public:
    kalibracja1D();


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


    ~kalibracja1D();
private:
    punktTCP P0;///wspolrzedne robota
    punkt vx;
    /**
      vx oraz vz sa to wektory okreslajace wspolczynniki kalibracji
      */
};

#endif // CKALIBRACJA1D_H
