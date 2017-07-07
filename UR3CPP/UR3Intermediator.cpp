#include "UR3Intermediator.h"
#include <QtGlobal>
#include <QtCore>
#include <QtEndian>
#include <QHostAddress>
#include <QDebug>
#include "UR3Message.h"

#define parseDouble( src_class, setter_suffix, data, offset){double val; memcpy(&val, &_data[offset], sizeof(val));val = bytesSwap(val);offset+=sizeof(val);src_class.set ## setter_suffix(val);}







static double RoundDouble(double val,int prec)
{
    auto precision = pow(10,prec);
    return round(val * precision) / precision;
}

char *strdup (const char *s)
{
    char* d = (char*)malloc(strlen (s) + 1);   // Space for length plus nul
    if (d == NULL) return NULL;          // No memory
    strcpy (d,s);                        // Copy the characters
    return d;                            // Return the new string
}

static double bytesSwap(double v)
{
    union {
        uint64_t i;
        double d;
    } conv;
    conv.d = v;
    conv.i = _byteswap_uint64(conv.i);
    return conv.d;

}
void UR3Intermediator::MoveToPoint(QVector<double> q, double JointAcceleration, double JointSpeed)
{
    //TODO: nie dziala, zla logika

    CartesianInfoData CurrentCartesianInfo = this->ActualRobotInfo.getCartesianInfoData();
    double x = RoundDouble(CurrentCartesianInfo.getX(),4);
    double y = RoundDouble(CurrentCartesianInfo.getY(),4);
    double z = RoundDouble(CurrentCartesianInfo.getZ(),4);
    double rx = RoundDouble(CurrentCartesianInfo.getRx(),4);
    double ry = RoundDouble(CurrentCartesianInfo.getRy(),4);
    double rz = RoundDouble(CurrentCartesianInfo.getRz(),4);

    QVector<double> cord = QVector<double>({x+(q[0]/1000.0),y+(q[1]/1000.0),z+(q[2]/1000.0),rx,ry,rz});
    MoveL(cord);
}

void UR3Intermediator::MoveJ(QVector<double> JointPosition, double JointAcceleration, double JointSpeed)
{
    // if(_running == true) qDebug()<<"rusza sie";
    CheckIfStillMovejRunning();
    if(_connected && _running==false)
    {
        //TODO :: ZAMIEN NA STRING PARAMETRY PRZEKAZYWANE W FUNKCJI

       // QString test = "movej([-0.1, -1.66, 1.71, -1.62, -1.56, 1.19], a=1.0, v=0.1)\n";

        QString command = "movej([" +
                QString::number(JointPosition[0]) + ", " +
                QString::number(JointPosition[1]) + ", " +
                QString::number(JointPosition[2]) + ", " +
                QString::number(JointPosition[3]) + ", " +
                QString::number(JointPosition[4]) + ", " +
                QString::number(JointPosition[5]) + "], " +
                "a=" + QString::number(JointAcceleration)+ ", " +
                "v=" + QString::number(JointSpeed)+ ")\n";

        //        _socket->write(command.toLatin1().data());
        //        _socket->waitForBytesWritten();
        cmds.push_back(command);
        _running = true;
        _moveJTargetPos = JointPosition;
        //qDebug()<<"zaczynam ruch";
    }
}

void UR3Intermediator::SpeedJ(QVector<double> qd, double a, double t)
{
    QString command = "speedj([" +
            QString::number(qd[0]) + ", " +
            QString::number(qd[1]) + ", " +
            QString::number(qd[2]) + ", " +
            QString::number(qd[3]) + ", " +
            QString::number(qd[4]) + ", " +
            QString::number(qd[5]) + "], " +
            "a=" + QString::number(a)+ ", " +
            "t=" + QString::number(t)+ ")\n";

    _socket->write(command.toLatin1().data());
    _socket->waitForBytesWritten();

}

void UR3Intermediator::SpeedL(QVector<double> qd, double a, double t)
{QString command = "speedl([" +
            QString::number(qd[0]) + ", " +
            QString::number(qd[1]) + ", " +
            QString::number(qd[2]) + ", " +
            QString::number(qd[3]) + ", " +
            QString::number(qd[4]) + ", " +
            QString::number(qd[5]) + "], " +
            "a=" + QString::number(a)+ ", " +
            "t=" + QString::number(t)+ ")\n";

    _socket->write(command.toLatin1().data());
    _socket->waitForBytesWritten();

}

void UR3Intermediator::SamuraiCut()
{
    MoveJ(QVector<double>({.0,-1.5708,.0,-1.5708,.0,.0}),2.0);
    MoveJ(QVector<double>({1.5962,0,.0,-1.5708,.0,.0}),2.0);
}

void UR3Intermediator::Home()
{
    MoveJ(QVector<double>({.0,-1.5708,.0,-1.5708,.0,.0}));
}

void UR3Intermediator::ForceMode(QVector<double> task_frame, QVector<double> selection_vector, QVector<double> wrench, int type, QVector<double> limits)
{
  /*  QString command = "force_mode([" +
            QString::number(task_frame[0]) + ", " +
            QString::number(task_frame[1]) + ", " +
            QString::number(task_frame[2]) + ", " +
            QString::number(task_frame[3]) + ", " +
            QString::number(task_frame[4]) + ", " +
            QString::number(task_frame[5]) + "], " +
            "selection vector[" +
            QString::number(selection_vector[0]) + ", " +
            QString::number(selection_vector[1]) + ", " +
            QString::number(selection_vector[2]) + ", " +
            QString::number(selection_vector[3]) + ", " +
            QString::number(selection_vector[4]) + ", " +
            QString::number(selection_vector[5]) + "], " +
            "wrench[" +
            QString::number(wrench[0]) + ", " +
            QString::number(wrench[1]) + ", " +
            QString::number(wrench[2]) + ", " +
            QString::number(wrench[3]) + ", " +
            QString::number(wrench[4]) + ", " +
            QString::number(wrench[5]) + "], " +
            "type=" + QString::number(type)+ ", " +
            "limits[" +
            QString::number(limits[0]) + ", " +
            QString::number(limits[1]) + ", " +
            QString::number(limits[2]) + ", " +
            QString::number(limits[3]) + ", " +
            QString::number(limits[4]) + ", " +
            QString::number(limits[5]) + "], " +
            ")\n";*/

    QString command = "def tesforce():\n force_mode(p[" +
            QString::number(task_frame[0]) + "," +
            QString::number(task_frame[1]) + "," +
            QString::number(task_frame[2]) + "," +
            QString::number(task_frame[3]) + "," +
            QString::number(task_frame[4]) + "," +
            QString::number(task_frame[5]) + "]," +
            "[" +
            QString::number(selection_vector[0]) + "," +
            QString::number(selection_vector[1]) + "," +
            QString::number(selection_vector[2]) + "," +
            QString::number(selection_vector[3]) + "," +
            QString::number(selection_vector[4]) + "," +
            QString::number(selection_vector[5]) + "]," +
            "[" +
            QString::number(wrench[0]) + "," +
            QString::number(wrench[1]) + "," +
            QString::number(wrench[2]) + "," +
            QString::number(wrench[3]) + "," +
            QString::number(wrench[4]) + "," +
            QString::number(wrench[5]) + "]," +
            "" + QString::number(type)+ "," +
            "[" +
            QString::number(limits[0]) + "," +
            QString::number(limits[1]) + "," +
            QString::number(limits[2]) + "," +
            QString::number(limits[3]) + "," +
            QString::number(limits[4]) + "," +
            QString::number(limits[5]) + "]" +
            ")\n movej(p[-0.362,-0.118,0.246,1.55,2.9,-0.12], a=1.3962634015954636, v=0.1471975511965976)\nend\n";

    qDebug()<<command;
    _socket->write(command.toLatin1().data());
    _socket->waitForBytesWritten();
}

void UR3Intermediator::Servoc(QVector<double> pose, double acceleration, double speed)
{
    QString command = "servoc(p[" +
            QString::number(pose[0]) + ", " +
            QString::number(pose[1]) + ", " +
            QString::number(pose[2]) + ", " +
            QString::number(pose[3]) + ", " +
            QString::number(pose[4]) + ", " +
            QString::number(pose[5]) + "], " +
            "a=" + QString::number(acceleration)+ ", " +
            "v=" + QString::number(speed)+ ")\n";
    if(cmds.length()>0)
        cmds.push_back(command);
    else
    {
        _socket->write(command.toLatin1().data());
        _socket->waitForBytesWritten();
    }
}

void UR3Intermediator::MoveL(QVector<double> TargetPose, double toolAcceleration, double toolSpeed, double time, double blendRadius)
{
    if(_connected && !_running)
    {
        //TODO :: ZAMIEN NA STRING PARAMETRY PRZEKAZYWANE W FUNKCJI, PRZETESTOWAC NA PRAWIDLOWYCH PZYCJACH


        QString commands = "movel([" +
                QString::number(TargetPose[0]) + ", " +
                QString::number(TargetPose[1]) + ", " +
                QString::number(TargetPose[2]) + ", " +
                QString::number(TargetPose[3]) + ", " +
                QString::number(TargetPose[4]) + ", " +
                QString::number(TargetPose[5]) + "], " +
                "a=" + QString::number(toolAcceleration)+ ", " +
                "v=" + QString::number(toolSpeed)+ ", " +
                "t=" + QString::number(time)+", "+
                "r=" + QString::number(blendRadius)+
                ")\n";

        _socket->write(command.toLatin1().data());
        _socket->waitForBytesWritten();
        _moveLTargetPose = TargetPose;
        _running = true;
    }

}

UR3Intermediator::UR3Intermediator():_connected(false), _running(false),Port(30002),IpAddress("192.168.149.128")
{
    this->_socket = new QTcpSocket();
    this->_lastJointPos.resize(6);
    this->_lastJointPos.fill(.0);
    this->_lastPolozenie.resize(6);
    this->_lastPolozenie.fill(.0);
    this->_lastForceValue.resize(6);
    this->_lastForceValue.fill(.0);

    connect(this->_socket,SIGNAL(readyRead()),this,SLOT(OnSocketNewBytesWritten()));
    connect(this->_socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    startTimer(1000);
}

UR3Intermediator::UR3Intermediator(QString ipAddress, int port):_connected(false), _running(false),Port(port),IpAddress(ipAddress)
{
    this->_socket = new QTcpSocket();
    this->_lastJointPos.resize(6);
    this->_lastJointPos.fill(.0);
    this->_lastPolozenie.resize(6);
    this->_lastPolozenie.fill(.0);
    this->_lastForceValue.resize(6);
    this->_lastForceValue.fill(.0);

    connect(this->_socket,SIGNAL(readyRead()),this,SLOT(OnSocketNewBytesWritten()));
    connect(this->_socket,SIGNAL(disconnected()),this,SLOT(disconnected()));

}

int UR3Intermediator::getPort() const
{
    return Port;
}

void UR3Intermediator::setPort(int value)
{
    Port = value;
}

QString UR3Intermediator::getIpAddress() const
{
    return IpAddress;
}

void UR3Intermediator::setIpAddress(const QString &value)
{
    IpAddress = value;
}

void UR3Intermediator::GetRobotData()
{
    int size = 0;
    unsigned int offset = 0;
    if(mutex.tryLock())
    {
        _data = _DataFlow.data();
        memcpy(&size, &_data[offset], sizeof(size));
        size = _byteswap_ulong(size);
        if(_DataFlow.size()<size)
        {
            mutex.unlock();
            return;
        }

        offset += sizeof(size);
        while(offset<size)
        {
            unsigned char Type;
            memcpy(&Type,&_data[offset],sizeof(Type));
            offset+=sizeof(Type);
            int messageType = Type;
            switch(messageType)
            {
            case ROBOT_MESSAGE:
            {

                break;
            }
            case ROBOT_STATE:
            {
                //qDebug()<<"ROBOT_STATE";
                GetRobotMessage(_data, offset, size);
                break;
            }
            case PROGRAM_STATE_MESSAGE:
            {
                break;
            }
            case 64:
            {

                RealTime(_data, offset, size);
                break;
            }
            default:
                offset = size;
                break;
            }

        }
        _DataFlow = _DataFlow.mid(size);
        //MoveJ(QVector<double>({-0.5, -1.26, 1.21, -1.12, -1.76, 1.09}));
        qDebug()<<this->ActualRobotInfo.robotModeData.getIsProgramRunning()<<" joint state:"<<this->ActualRobotInfo.jointsData[0].getJointMode();
        /*qDebug()<<this->ActualRobotInfo.cartesianInfoData.getY();
                qDebug()<<this->ActualRobotInfo.cartesianInfoData.getZ();

                qDebug()<<this->ActualRobotInfo.cartesianInfoData.getRx();
                qDebug()<<this->ActualRobotInfo.cartesianInfoData.getRy();
                qDebug()<<this->ActualRobotInfo.cartesianInfoData.getRz();*/
        //MoveL(QVector<double>({-255.0,-194,630.0,0.5,1.9,-1.9}));


        mutex.unlock();
    }

}
void UR3Intermediator::CheckIfStillMovejRunning()
{

    //    QVector<JointData> jointsData = this->ActualRobotInfo.getJointsData();
    //    double firstJointPos = RoundDouble(jointsData[0].getActualJointPosition(),4);
    //    double secondJointPos = RoundDouble(jointsData[1].getActualJointPosition(),4);
    //    double thirdJointPos = RoundDouble(jointsData[2].getActualJointPosition(),4);
    //    double fourthJointPos = RoundDouble(jointsData[3].getActualJointPosition(),4);
    //    double fifthJointPos = RoundDouble(jointsData[4].getActualJointPosition(),4);
    //    double sixthJointPos = RoundDouble(jointsData[5].getActualJointPosition(),4);
    //    QVector<double> current = QVector<double>
    //    ({firstJointPos,secondJointPos,thirdJointPos,fourthJointPos,fifthJointPos,sixthJointPos});
    //    QVector<double> target = QVector<double>
    //            ({RoundDouble(jointsData[0].getTargetJointPosition(),4),RoundDouble(jointsData[1].getTargetJointPosition(),4),
    //             RoundDouble(jointsData[2].getTargetJointPosition(),4),RoundDouble(jointsData[3].getTargetJointPosition(),4),
    //             RoundDouble(jointsData[4].getTargetJointPosition(),4),RoundDouble(jointsData[5].getTargetJointPosition(),4)});
    //    if(current == _moveJTargetPos)
    //    {
    //        _running = false;
    //        //qDebug()<<"przestal sie ruszac";
    //    }
    _running =ActualRobotInfo.robotModeData.getIsProgramRunning();
}

void UR3Intermediator::CheckIfStillMoveLRunning()
{
    CartesianInfoData CurrentCartesianInfo = this->ActualRobotInfo.getCartesianInfoData();

    double x = RoundDouble(CurrentCartesianInfo.getX(),4);
    double y = RoundDouble(CurrentCartesianInfo.getY(),4);
    double z = RoundDouble(CurrentCartesianInfo.getZ(),4);
    double rx = RoundDouble(CurrentCartesianInfo.getRx(),4);
    double ry = RoundDouble(CurrentCartesianInfo.getRy(),4);
    double rz = RoundDouble(CurrentCartesianInfo.getRz(),4);

    QVector<double> current = QVector<double>({x,y,z,rx,ry,rz});

    if(current == _moveLTargetPose){
        _running = false;
    }


}

void UR3Intermediator::CheckJointsPosChanged()
{
    QVector<JointData> jointsData = this->ActualRobotInfo.getJointsData();
    double firstJointPos = RoundDouble(jointsData[0].getActualJointPosition(),4);
    double secondJointPos = RoundDouble(jointsData[1].getActualJointPosition(),4);
    double thirdJointPos = RoundDouble(jointsData[2].getActualJointPosition(),4);
    double fourthJointPos = RoundDouble(jointsData[3].getActualJointPosition(),4);
    double fifthJointPos = RoundDouble(jointsData[4].getActualJointPosition(),4);
    double sixthJointPos = RoundDouble(jointsData[5].getActualJointPosition(),4);
    QVector<double> current = QVector<double>
            ({firstJointPos,secondJointPos,thirdJointPos,fourthJointPos,fifthJointPos,sixthJointPos});

    if(current != _lastJointPos){
        _lastJointPos = current;
        emit newPoseTCP(current, 't');

    }
}

void UR3Intermediator::CheckPolozenieChanged()
{
    CartesianInfoData CurrentCartesianInfo = this->ActualRobotInfo.getCartesianInfoData();

    double x = RoundDouble(CurrentCartesianInfo.getX(),4);
    double y = RoundDouble(CurrentCartesianInfo.getY(),4);
    double z = RoundDouble(CurrentCartesianInfo.getZ(),4);
    double rx = RoundDouble(CurrentCartesianInfo.getRx(),4);
    double ry = RoundDouble(CurrentCartesianInfo.getRy(),4);
    double rz = RoundDouble(CurrentCartesianInfo.getRz(),4);

    QVector<double> current = QVector<double>({x,y,z,rx,ry,rz});

    if(current !=_lastPolozenie){
        _lastPolozenie = current;
        emit newPoseTCP(current, 't');
    }

}


void UR3Intermediator::CheckForceChanged()
{
    ForceModeData forcesModeData = this->ActualRobotInfo.getForceModeData();
    //= this->ActualRobotInfo.getForcesData();
    QVector<double> current;
    current.resize(6);
    //for(int i=0;i<6;i++)
    //   current[i] = RoundDouble(forcesModeData.getActualForceValue(),4);
    current[0] = forcesModeData.getFX();
    current[1] = forcesModeData.getFY();
    current[2] = forcesModeData.getFZ();
    current[3] = forcesModeData.getRx();
    current[4] = forcesModeData.getRy();
    current[5] = forcesModeData.getRz();

    //if(current != _lastForceValue){
    _lastForceValue = current;
    //qDebug()<<"Wyemitowno";
    emit newPoseTCP(current, 'f');

    //}
}

void UR3Intermediator::GetRobotMessage(char *data, unsigned int &offset, int size)
{
    while(size>offset){
        int sizeOfPackage;
        memcpy(&sizeOfPackage, &data[offset], sizeof(sizeOfPackage));
        sizeOfPackage = _byteswap_ulong(sizeOfPackage);
        //sizeOfPackage = qFromBigEndian<int>(sizeOfPackage);
        offset+=sizeof(sizeOfPackage);

        unsigned char packageType;
        memcpy(&packageType, &data[offset], sizeof(packageType));
        offset+=sizeof(packageType);
        //  packageType = FORCE_MODE_DATA;
        switch(packageType){
        case ROBOT_MODE_DATA:
            this->ActualRobotInfo.setRobotModeData(_data, offset);
            if(ActualRobotInfo.robotModeData.getIsEmergencyStopped() || ActualRobotInfo.robotModeData.getIsProtectiveStopped()){

                _socket->write(QString("end_force_mode()\n").toLatin1().data());
                _socket->waitForBytesWritten();
            }
            break;
        case JOINT_DATA:
            this->ActualRobotInfo.setJointsData(_data, offset);
            /*if(_running)
            {
                CheckIfStillMovejRunning();
            }*/
            CheckJointsPosChanged();
            break;
        case TOOL_DATA:
            this->ActualRobotInfo.setToolData(_data,offset);
            break;
        case MASTERBOARD_DATA:
            this->ActualRobotInfo.setMasterboardData(_data, offset);
            break;
        case CARTESIAN_INFO:
            this->ActualRobotInfo.setCartesianInfoData(_data,offset);
            if(_running)
            {
                CheckIfStillMoveLRunning();
            }
            CheckPolozenieChanged();
            break;
        case KINEMATICS_INFO:
            break;
        case CONFIGURATION_DATA:
            break;
        case FORCE_MODE_DATA:
            qDebug()<<"Force mode";
            this->ActualRobotInfo.setForceModeData(_data, offset);

            CheckForceChanged();

            break;
        case ADDITIONAL_INFO:
            break;
        case CALIBRATION_DATA:
            break;
        case SAFETY_DATA:
            break;
        }
        offset +=sizeOfPackage - 5; //-5 poniewaz wczesniej przesunalem o sizeofpackage i packagetype
    }

}

void UR3Intermediator::ReadDataFlow()
{
    if(_connected)
    {
        if(mutex.tryLock())
        {
            _DataFlow.push_back( this->_socket->readAll());

            mutex.unlock();
        }

    }
}

void UR3Intermediator::RealTime(char *_data, unsigned int &offset, int size)
{
    QTargetJointsPositions TargetJointsPositions;
    QTargetJointsVelocities TargetJointsVelocities;
    QTargetJointsTorques TargetJointsTorques;
    QActualJointsPositions ActualJointsPositions;
    QActualJointsCurrents ActualJointsCurrents;
    QActualCartesianCoordinatesTCP ActualCartesianCoordinatesTCP;
    QTCPForces TCPForces;
    QTargetCartesianCoordinatesTCP TargetCartesianCoordinatesTCP;
    QRobotMode RobotMode;



    offset += 7;

    //qtarget
    /*parseDouble(TargetJointsPositions,Kat1,data,offset);
    parseDouble(TargetJointsPositions,Kat2,data,offset);
    parseDouble(TargetJointsPositions,Kat3,data,offset);
    parseDouble(TargetJointsPositions,Kat4,data,offset);
    parseDouble(TargetJointsPositions,Kat5,data,offset);
    parseDouble(TargetJointsPositions,Kat6,data,offset);*/
    offset += 48;

    //qdtarget
    parseDouble(TargetJointsVelocities,Predkosc1,data,offset);
    parseDouble(TargetJointsVelocities,Predkosc2,data,offset);
    parseDouble(TargetJointsVelocities,Predkosc3,data,offset);
    parseDouble(TargetJointsVelocities,Predkosc4,data,offset);
    parseDouble(TargetJointsVelocities,Predkosc5,data,offset);
    parseDouble(TargetJointsVelocities,Predkosc6,data,offset);
    //offset += 48;

    //qddtarget
//    offset += 48;

    //itarget
//    offset += 48;

    //mtarget
    /*parseDouble(TargetJointsTorques,Torque1,data,offset);
    parseDouble(TargetJointsTorques,Torque2,data,offset);
    parseDouble(TargetJointsTorques,Torque3,data,offset);
    parseDouble(TargetJointsTorques,Torque4,data,offset);
    parseDouble(TargetJointsTorques,Torque5,data,offset);
    parseDouble(TargetJointsTorques,Torque6,data,offset);*/
//    offset += 48;

    //qactual
    /*parseDouble(ActualJointsPositions,Kat1,data,offset);
    parseDouble(ActualJointsPositions,Kat2,data,offset);
    parseDouble(ActualJointsPositions,Kat3,data,offset);
    parseDouble(ActualJointsPositions,Kat4,data,offset);
    parseDouble(ActualJointsPositions,Kat5,data,offset);
    parseDouble(ActualJointsPositions,Kat6,data,offset);*/
//    offset += 48;

    //qdactual

//    offset += 48;

    //iactual
    /*parseDouble(ActualJointsCurrents,Current1,data,offset);
    parseDouble(ActualJointsCurrents,Current2,data,offset);
    parseDouble(ActualJointsCurrents,Current3,data,offset);
    parseDouble(ActualJointsCurrents,Current4,data,offset);
    parseDouble(ActualJointsCurrents,Current5,data,offset);
    parseDouble(ActualJointsCurrents,Current6,data,offset);*/
//    offset += 48;

    //icontrol
//    offset += 48;

    //toolvectoractual
    /*parseDouble(ActualCartesianCoordinatesTCP,X,data,offset);
    parseDouble(ActualCartesianCoordinatesTCP,Y,data,offset);
    parseDouble(ActualCartesianCoordinatesTCP,Z,data,offset);
    parseDouble(ActualCartesianCoordinatesTCP,Rx,data,offset);
    parseDouble(ActualCartesianCoordinatesTCP,Ry,data,offset);
    parseDouble(ActualCartesianCoordinatesTCP,Rz,data,offset);*/
//    offset += 48;

    //toolspeedactual
//    offset += 48;

    //tcpforce
    /*parseDouble(TCPForces,Fx,data,offset);
    parseDouble(TCPForces,Fy,data,offset);
    parseDouble(TCPForces,Fz,data,offset);
    parseDouble(TCPForces,Tx,data,offset);
    parseDouble(TCPForces,Ty,data,offset);
    parseDouble(TCPForces,Tz,data,offset);*/
//    offset += 48;

    //toolvectortarget
   /* parseDouble(TargetCartesianCoordinatesTCP,X,data,offset);
    parseDouble(TargetCartesianCoordinatesTCP,Y,data,offset);
    parseDouble(TargetCartesianCoordinatesTCP,Z,data,offset);
    parseDouble(TargetCartesianCoordinatesTCP,Rx,data,offset);
    parseDouble(TargetCartesianCoordinatesTCP,Ry,data,offset);
    parseDouble(TargetCartesianCoordinatesTCP,Rz,data,offset);*/
//    offset += 48;

    //tcpspeedtarget
//    offset += 48;

    //digitalinputsbits
//    offset += 8;

    //motortemperatures
//    offset += 48;

    //controllertimer
//    offset += 8;

    //testvalue
//    offset += 8;

    //robotmode
    //parseDouble(RobotMode,Mode,data,offset);
//    offset += 8;

    //jointmodes
//    offset += 48;

    //safetymode
//    offset += 8;
    //
//    offset += 48;

    //toolaccelerometervalues
//    offset += 24;

    //
//    offset += 8;

    //speedscalling
//    offset += 8;

    //linearmomentumnorm
//    offset += 8;

    //
//    offset += 8;

    //
//    offset += 8;

    //vmain
//    offset += 8;

    //vrobot
//    offset += 8;

    //irobot
//    offset += 8;

    //vactual


    /*qDebug()<<"kat1: "<<TargetJointsPositions.getKat1()*57;
    qDebug()<<"kat2: "<<TargetJointsPositions.getKat2()*57;
    qDebug()<<"kat3: "<<TargetJointsPositions.getKat3()*57;
    qDebug()<<"kat4: "<<TargetJointsPositions.getKat4()*57;
    qDebug()<<"kat5: "<<TargetJointsPositions.getKat5()*57;
    qDebug()<<"kat6: "<<TargetJointsPositions.getKat6()*57;*/

    qDebug()<<"predkosc1: "<<TargetJointsVelocities.getPredkosc1();
    qDebug()<<"predkosc2: "<<TargetJointsVelocities.getPredkosc2();
    qDebug()<<"predkosc3: "<<TargetJointsVelocities.getPredkosc3();
    qDebug()<<"predkosc4: "<<TargetJointsVelocities.getPredkosc4();
    qDebug()<<"predkosc5: "<<TargetJointsVelocities.getPredkosc5();
    qDebug()<<"predkosc6: "<<TargetJointsVelocities.getPredkosc6();

    /* qDebug()<<"moment1: "<<TargetJointsTorques.getTorque1();
     qDebug()<<"moment2: "<<TargetJointsTorques.getTorque2();
     qDebug()<<"moment3: "<<TargetJointsTorques.getTorque3();
     qDebug()<<"moment4: "<<TargetJointsTorques.getTorque4();
     qDebug()<<"moment5: "<<TargetJointsTorques.getTorque5();
     qDebug()<<"moment6: "<<TargetJointsTorques.getTorque6();*/

    /* qDebug()<<"kat1: "<<ActualJointsPositions.getKat1();
     qDebug()<<"kat2: "<<ActualJointsPositions.getKat2();
     qDebug()<<"kat3: "<<ActualJointsPositions.getKat3();
     qDebug()<<"kat4: "<<ActualJointsPositions.getKat4();
     qDebug()<<"kat5: "<<ActualJointsPositions.getKat5();
     qDebug()<<"kat6: "<<ActualJointsPositions.getKat6();*/

     /*qDebug()<<"prad1: "<<ActualJointsCurrents.getCurrent1();
     qDebug()<<"prad2: "<<ActualJointsCurrents.getCurrent2();
     qDebug()<<"prad3: "<<ActualJointsCurrents.getCurrent3();
     qDebug()<<"prad4: "<<ActualJointsCurrents.getCurrent4();
     qDebug()<<"prad5: "<<ActualJointsCurrents.getCurrent5();
     qDebug()<<"prad6: "<<ActualJointsCurrents.getCurrent6();*/

     /*qDebug()<<"wspolrzedna x tcp: "<<ActualCartesianCoordinatesTCP.getX();
     qDebug()<<"wspolrzedna y tcp: "<<ActualCartesianCoordinatesTCP.getY();
     qDebug()<<"wspolrzedna z tcp: "<<ActualCartesianCoordinatesTCP.getZ();
     qDebug()<<"Orientacja Rx tcp: "<<ActualCartesianCoordinatesTCP.getRx();
     qDebug()<<"Orientacja Ry tcp: "<<ActualCartesianCoordinatesTCP.getRy();
     qDebug()<<"Orientacja Rz tcp: "<<ActualCartesianCoordinatesTCP.getRz();*/

    /* qDebug()<<"sila Fx tcp: "<<TCPForces.getFx();
     qDebug()<<"sila Fy tcp: "<<TCPForces.getFy();
     qDebug()<<"sila Fz tcp: "<<TCPForces.getFz();
     qDebug()<<"moment Tx tcp: "<<TCPForces.getTx();
     qDebug()<<"moment Ty tcp: "<<TCPForces.getTy();
     qDebug()<<"moment Tz tcp: "<<TCPForces.getTz();*/

     /*qDebug()<<"docelowa pozycja x TCP: "<<TargetCartesianCoordinatesTCP.getX();
     qDebug()<<"docelowa pozycja y TCP: "<<TargetCartesianCoordinatesTCP.getY();
     qDebug()<<"docelowa pozycja z TCP: "<<TargetCartesianCoordinatesTCP.getZ();
     qDebug()<<"docelowa orientacja Rx TCP: "<<TargetCartesianCoordinatesTCP.getRx();
     qDebug()<<"docelowa orientacja Ry TCP: "<<TargetCartesianCoordinatesTCP.getRy();
     qDebug()<<"docelowa orientacja Rz TCP: "<<TargetCartesianCoordinatesTCP.getRz();*/

     //qDebug()<<"tryb robota: "<<RobotMode.getMode();
}

bool UR3Intermediator::ConnectToRobot()
{

    if (_connected == false)
    {
        _socket->connectToHost(IpAddress,Port);
        if(_socket->waitForConnected())
        {
            _connected = true;
        }
        else
        {
            _connected = false;
        }
    }
    emit ConnectionAction(this->IpAddress.toLatin1().data(),_connected);
    return _connected;


}

void UR3Intermediator::disconnected()
{
    _connected = false;
    _socket->deleteLater();
    _socket = new QTcpSocket();
    ConnectToRobot();
}

void UR3Intermediator::OnTcpChanged()
{

}

void UR3Intermediator::OnSocketNewBytesWritten()
{
    this->ReadDataFlow();
    GetRobotData();
}
