#ifndef CMYO_H
#define CMYO_H

#include <QObject>
#include <QVector>
#include <UR3Intermediator.h>
#include <myoform.h>
class cMYO : public QObject
{
    Q_OBJECT
public:
    explicit cMYO(UR3Intermediator* robot, QObject *parent = 0);
    void sprawdz_ruch();
    QWidget *getWidget();

    QString getIP() const;
    void setIP(const QString &IP);

private:
    Q_PROPERTY(QString adresIP READ getIP WRITE setIP USER true)
    QString m_IP;
    int m_port;
    UR3Intermediator* m_robot;
    MYOForm* widget;

signals:

    void przesun_o_wektor(vector<double> xyz);
    void rotacja(double kat);
    void koncowka(bool zacisniete);
    void nowyGest(QString);

public slots:
    void settings(QString IP, int port);
    void polacz_z_myo(); // zazwyczaj ws://127.0.0.1:10138/myo/3

};

#endif // CMYO_H
