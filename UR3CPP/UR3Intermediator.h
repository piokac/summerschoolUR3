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

    /**
     * @brief ConnectToRobot - próbuje połączyć się z robotem na podstawie aktualnego ip i portu podanego w konstruktorze
     * @return
     */
    bool ConnectToRobot();

    void MoveC(QVector<double> position_via, QVector<double> TargetPose, double toolAcceleration = 1.2, double toolSpeed=0.25, double blendRadius = 0);
    /**
     * @brief MoveJ
     * @param JointPosition - docelowa pozycja jointów [rad]
     * @param JointAcceleration - przyśpieszenie z jakim obracają się jointy, domyślnie 1.0
     * @param JointSpeed - prędkość obracających się jointów, domyślnie 0.1
     */
    void MoveJ(QVector<double> JointPosition, double JointAcceleration= 1.0, double JointSpeed = 0.1);
    void MoveP(QVector<double> TargetPose,double toolAcceleration,double toolSpeed,double blendRadius);
    /**
     * @brief MoveL
     * @param TargetPose - docelowa pozycja TCP [rad]
     * @param toolAcceleration - przyśpieszenie z jakim obracają się jointy, domyślnie 1.2
     * @param toolSpeed - prędkość obracających się jointów, domyślnie 0.25
     */
    void MoveL(QVector<double> TargetPose,double toolAcceleration=1.2,double toolSpeed=.25,double time=0, double blendRadius=0);
    /**
     * @brief SpeedJ
     * @param qd - docelowa pozycja jointów [rad]
     * @param a - przyśpieszenie z jakim obracają się jointy, domyślnie 1.2
     * @param t - czas
     */
    void SpeedJ(QVector<double> qd, double a=.1, double t=0.4);
    void SpeedL(QVector<double> qd, double a=.1, double t=0.4);
    /**
     * @brief SamuraiCut - funkcja, testowa, imitująca cięcie kataną po skosie
     */
    void SamuraiCut();
    /**
     * @brief Home - ustawia robota do pozycji początkowej
     */
    void Home();

    /**
     * @brief ForceMode - sterowanie siłami
     */
    void ForceMode(QVector<double> task_frame, QVector<double> selection_vector, QVector<double> wrench, int type, QVector<double> limits);

    /**
     * @brief ForceMode - sterowanie bez zwalniania
     */
    void Servoc(QVector<double> pose, double acceleration = 1.2, double speed = 0.25);



    UR3Intermediator();
    /**
     * @brief konstruktor dla klasy
     * @param ipAddress - Adres ip socketu
     * @param port - port
     */
    UR3Intermediator(QString ipAddress, int port);
    /**
     * @brief GetActualUR3State
     * @return zwraca ogól aktualnych informacji o robocie; podstawowe źródło informacji
     */
    UR3Message GetActualUR3State();



    int getPort() const;
    void setPort(int value);

    QString getIpAddress() const;
    void setIpAddress(const QString &value);

signals:
    //umieszczone w jednym sygnale, dwa sygnaly z argumentami qvector crashuja aplikacje, najprawdopdobniej blad mingw 4.9.2
    void newPoseTCP(QVector<double> x, char flag);  /*!< Sygnal przekazujacy TCP albo pose jointwo, w zaleznosci od flagi, 'p' - pose, 't' - tcp  */
    void ConnectionAction(char* Ip,bool Result);
private:

    //Fields

    bool _running;
    QVector<double> _moveJTargetPos;
    QVector<double> _moveLTargetPose;
    QVector<double> _lastJointPos;
    QVector<double> _lastPolozenie;
    QVector<double> _lastForceValue;

    Q_PROPERTY(int PortTCP READ getPort WRITE setPort USER true)
    int Port;

    Q_PROPERTY(QString IUR3_IP READ getIpAddress WRITE setIpAddress USER true)
    QString IpAddress;

    UR3Message ActualRobotInfo;
    char * _data;
    QByteArray _DataFlow;
    QTcpSocket* _socket;
    bool _connected;

    //Methods
    void CheckForceChanged();
    void CheckIfStillMovejRunning();
    void CheckIfStillMoveLRunning();
    void CheckJointsPosChanged();
    void CheckPolozenieChanged();
    void GetRobotData();
    void GetRobotMessage(char * data, unsigned int &offset, int size);
    void ReadDataFlow();
    void RealTime(char * data, unsigned int &offset, int size);

    void timerEvent(QTimerEvent *event);

private slots:
    void disconnected();


public slots:

    void OnTcpChanged();
    void OnSocketNewBytesWritten();
private:
    QMutex mutex;
    QVector<QString> cmds;
};


#endif // UR3INTERMEDIATOR_H
