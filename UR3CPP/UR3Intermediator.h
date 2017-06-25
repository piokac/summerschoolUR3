#ifndef UR3INTERMEDIATOR_H
#define UR3INTERMEDIATOR_H


#pragma once
#include <vector>
#include "UR3Message.h"
#include "UR3MessageOut.h"
#include <string>
#include <QObject>
#include <QTcpSocket>
#include <QMutex>

using namespace std;

class UR3Intermediator: public QObject
{
    Q_OBJECT

public:

    void MoveToPoint(QVector<double> q,double JointAcceleration= 1.0, double JointSpeed = 0.1);

    void MoveC(QVector<double> position_via, QVector<double> TargetPose, double toolAcceleration = 1.2, double toolSpeed=0.25, double blendRadius = 0);
    void MoveJ(QVector<double> JointPosition, double JointAcceleration= 1.0, double JointSpeed = 0.1);
    void MoveP(QVector<double> TargetPose,double toolAcceleration,double toolSpeed,double blendRadius);
    void MoveL(QVector<double> TargetPose,double toolAcceleration=1.2,double toolSpeed=.25,double time=0, double blendRadius=0);

    UR3Intermediator();
    UR3Message GetActualUR3State();



    int getPort() const;
    void setPort(int value);

    QString getIpAddress() const;
    void setIpAddress(const QString &value);

signals:
    //umieszczone w jednym sygnale, dwa sygnaly z argumentami qvector crashuja aplikacje, najprawdopdobniej blad mingw 4.9.2
    void newPoseTCP(QVector<double> x, char flag);  /*!< Sygnal przekazujacy TCP albo pose jointwo, w zaleznosci od flagi, 'p' - pose, 't' - tcp  */

private:

    //Fields

    bool _running;
    QVector<double> _moveJTargetPos;
    QVector<double> _lastJointPos;
    QVector<double> _lastPolozenie;

    //Q_PROPERTY(int Port READ getPort WRITE setPort USER true)
    int Port;

    //Q_PROPERTY(QString IpAddress READ getIpAddress WRITE setIpAddress USER true)
    QString IpAddress;

    UR3Message ActualRobotInfo;
    char * _data;
    QByteArray _DataFlow;
    QTcpSocket* _socket;
    bool _connected;

    //Methods
    void CheckIfStillMovejRunning();
    void CheckJointsPosChanged();
    void CheckPolozenieChanged();
    void GetRobotData();
    void GetRobotMessage(char * data, unsigned int &offset, int size);
    QByteArray ReadDataFlow();
    bool ConnectToRobot();
private slots:
    void disconnected();


public slots:

    void OnTcpChanged();
    void OnSocketNewBytesWritten();
private:
    QMutex mutex;
};


#endif // UR3INTERMEDIATOR_H
