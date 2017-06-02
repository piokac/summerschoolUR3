#ifndef CKALIBRACJA3D_H
#define CKALIBRACJA3D_H

#include <QObject>
#include"kalibracja.h"

class cKalibracja3d: public kalibracja
{
public:
    kalibracja3D();
    /**
      kalibracja3D jest najbardziej rozbudowanym modulem kalibracyjnym, przyjmujacym 3 punkty. Modul umozliwia
      poruszanie sie robota w 3D. Przydatne jest to np. do modulu poliline. Ustawiamy wtedy 3 punkty
      np. dolny lewy rog kartki, prawy dolny rog oraz jeden gorny, dzieki czemu manipulator moze swobodnie
      poruszac sie w kazda strone.
      Dla zgodnosci ustalamy, ze skara poruszania jest od 0 do 1, tzn. dolny lewy rog to <0,0,0>,
      dolny prawy rog to <1,0,0>, gorny lewy to <0,1,0> etc, wg schematu <wspolrzedna x, wsp. y, wsp. z>

      nalezy uwazac na mozliwosc, ze kartka bedzie inna niz kwadratowa. modul kalibracji nie
      bedzie zabezpieczal proporcji co moze sprawic, ze jesli zechcemy przesunac robota
      o <0.1 , 0.1, 0> moze sie okazac, ze wg osi x przesunie sie np. dwukrotnie bardziej niz wg osi y.

      wysokosc wg wspolrzednych "z" dla zgodnosci narzucamy, ze bedzie ona posiadala taka sama proporcje
      jak wspolrzedna "x".
      */


protected:
    void kalibruj(QVector<punkt> pkt);


public:
    void kalibruj();
     ///kalibruje punkty i posiada cala ligike kalibracji. To kalibruj jest wywolywane do np. pobrania punktow
     /// robota.
    QVector<punktTCP> transformuj(QVector<punkt> wektor);
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
