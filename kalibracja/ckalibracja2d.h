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
   /**
     Klasa ma za zadanie kalibrowac punkty znajdujace sie w jednej lini. Przydatne do kalibracji np. klawiatury.
     ustawiamy wtedy punkt poczatkowy np. klawisz "q" a puzniej punkt koncowy np. klawisz "p".
     Wtedy dla kozystajacego z modulu kalibracji klawisz "q" bedzie mial wartosc <0,0>
     natomiast "p" bedzie mial wartosc <1,0> poniewaz poruszac bedziemy sie w skali od 0 do 1.
     druga wspolrzedna oznacza wysokosc. T.j. jesli wartosc bedzie wynosila 0, oznacza, ze klawisz bedzie
     wcisniety, natomiast wartosc 1 bd oznaczala podniesiony manipulator, wykorzystywany np podczas zmiany klawisza.
     */

protected:
    void kalibruj(QVector<punkt> pkt);


public:
    void kalibruj();
     ///kalibruje punkty
    QVector<punktTCP> transformuj(QVector<punkt> wektor);
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
