#include "clogger.h"
#include <QDebug>
#include<QTimer>

cLogger::cLogger(QObject *parent) : QObject(parent)
{
    connect(&ur3, SIGNAL(newLog(int, char, QVector<double>)),this, SLOT(slot_turn(int, char, QVector<double>)));
    flag = 0;
}

void cLogger::Open(QString SaveFileName)
{
    file.setFileName(SaveFileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        // stream<<str<< ", " << x << ", " << y << ", " << z << ", " << rx << ", " << ry << ", " << rz << ", " << fx << ", " << fy << ", " << fz << "\n";
        //aktualny czas, położenie, kąty, siły
        stream.setDevice(&file);
        // stream<<"Test";
        // stream.flush();
        file.close();
        flag = 1;
    }
}
void cLogger::Close()
{
    flag = 0;
}

void cLogger::Open()
{
    flag = 1;
}

void cLogger::slot_turn(int devId, char id, QVector<double> vec)
{
    if ( flag == 1 && devId == 1) //file.isOpen(
    {
        /*  QTimer *timer = new QTimer(this);
           connect(timer, SIGNAL(timeout()), this, SLOT(update()));
           timer->start();*/
       /* QTimer timer;
        timer.start();
        qDebug()<<timer.interval();*/

        QString format = "hh::mm:ss:zzz";
        QString str=QTime::currentTime().toString(format);

        if (id == 'f')
        {
            file.open(QIODevice::WriteOnly | QIODevice::Append);
            stream.setDevice(&file);
            stream<<str<<", "<<vec[0]<<", "<<vec[1]<<", "<<vec[2]<<"\r\n";
            stream.flush();
            qDebug()<<"f";//<<stream;
            file.close();
        }
        if (id == 't')
        {
            file.open(QIODevice::WriteOnly | QIODevice::Append);
            stream.setDevice(&file);
            stream<<str<<", "<<vec[0]<<", "<<vec[1]<<", "<<vec[2]<<vec[3]<<", "<<vec[4]<<", "<<vec[5]<<"\r\n";
            stream.flush();
            qDebug()<<"t";//<<stream;
            file.close();
        }
    }
}
