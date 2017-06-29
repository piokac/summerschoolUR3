#include "ckalibracja3d.h"

cKalibracja3d::cKalibracja3d()
{

}



void cKalibracja3d::kalibruj()
{
    //wiza
}

QVector<punktTCP> cKalibracja3d::transformuj(QVector<punkt> wektor)
{
    for(auto itr=wektor.begin();itr<wektor.end(); itr++)
    {
        wektor[itr]=kalibruj3D(wektor[itr]);
    }
}
