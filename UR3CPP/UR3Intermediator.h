#ifndef UR3INTERMEDIATOR_H
#define UR3INTERMEDIATOR_H


#pragma once
#include <vector>
#include "UR3Message.h"
#include "UR3MessageOut.h"
#include <string>
#include <QObject>
#include <QTcpSocket>

using namespace std;

class UR3Intermediator: public QObject
{
    Q_OBJECT

public:

    void MoveJ(QVector<double> JointPosition,double JointAcceleration, double JointSpeed, double Time, double BlendRadius);
    void MoveP(QVector<double> TargetPose,double toolAcceleration,double toolSpeed,double blendRadius);
    void MoveL(QVector<double> TargetPose,double toolAcceleration,double toolSpeed,double time, double blendRadius);

    UR3Intermediator();
    UR3Message GetActualUR3State();

signals:

    void newTCP(QVector<double> pose);

private:

    //Fields

    int Port;
    QString IpAddress;
    UR3Message* ActualRobotInfo;

    QByteArray _DataFlow;
    QTcpSocket* _socket;
    bool _connected;

    //Methods

    UR3Message GetRobotMessage(const QByteArray& DataFlow);
    QByteArray ReadDataFlow();
    bool ConnectToRobot();


public slots:

    void OnTcpChanged();
    void OnSocketNewBytesWritten();
};


#endif // UR3INTERMEDIATOR_H
