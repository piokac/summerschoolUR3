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

    void MoveJ(QVector<double> JointPosition, double JointAcceleration= 1.0, double JointSpeed = 0.1);
    void MoveP(QVector<double> TargetPose,double toolAcceleration,double toolSpeed,double blendRadius);
    void MoveL(QVector<double> TargetPose,double toolAcceleration,double toolSpeed,double time, double blendRadius);

    UR3Intermediator();
    UR3Message GetActualUR3State();



signals:

    void newTCP(QVector<double> pose);

private:

    //Fields

    bool _running;
    QVector<double> _moveJTargetPos;
    int Port;
    QString IpAddress;
    UR3Message ActualRobotInfo;
    char * _data; //tutaj bedziemy przechowywac dataflow
    QByteArray _DataFlow;
    QTcpSocket* _socket;
    bool _connected;

    //Methods
    void CheckIfStillMovejRunning();

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
