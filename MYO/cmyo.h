#ifndef CMYO_H
#define CMYO_H

#include <QObject>
#include <QVector>

class cMYO : public QObject
{
    Q_OBJECT
public:
    explicit cMYO(QObject *parent = 0);
    void sprawdz_ruch();

private:
    QString m_IP;
    int m_port;

signals:
    void przesun_o_wektor(vector<double> xyz);
    void rotacja(double kat);
    void koncowka(bool zacisniete);

public slots:
    void polacz_z_myo(QString IP, int port); // zazwyczaj ws://127.0.0.1:10138/myo/3

};

#endif // CMYO_H
