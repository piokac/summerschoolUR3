#include "UR3Intermediator.h"
#include <QtGlobal>
#include <QtCore>
#include <QtEndian>
#include <QHostAddress>
#include <QDebug>
#include "UR3Message.h"
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
static double RoundDouble(double val,int prec)
{
    auto precision = pow(10,prec);
    return round(val * precision) / precision;
}

void UR3Intermediator::MoveJ(QVector<double> JointPosition, double JointAcceleration, double JointSpeed)
{
    if(_connected && !_running)
    {
        //TODO :: ZAMIEN NA STRING PARAMETRY PRZEKAZYWANE W FUNKCJI

        QString test = "movej([-0.1, -1.66, 1.71, -1.62, -1.56, 1.19], a=1.0, v=0.1)\n";

        QString command = "movej([" +
                QString::number(JointPosition[0]) + ", " +
                QString::number(JointPosition[1]) + ", " +
                QString::number(JointPosition[2]) + ", " +
                QString::number(JointPosition[3]) + ", " +
                QString::number(JointPosition[4]) + ", " +
                QString::number(JointPosition[5]) + "], " +
                "a=" + QString::number(JointAcceleration)+ ", " +
                "v=" + QString::number(JointSpeed)+ ")\n";

        _socket->write(command.toLatin1().data());
        _socket->waitForBytesWritten();
        _running = true;
    }
}

UR3Intermediator::UR3Intermediator():_connected(false),Port(30002),IpAddress("192.168.149.128")
{
    this->_socket = new QTcpSocket();
    this->_lastJointPos.fill(.0);
    //this->_lastPolozenie.fill(.0);
    connect(this->_socket,SIGNAL(readyRead()),this,SLOT(OnSocketNewBytesWritten()));
    connect(this->_socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    ConnectToRobot();

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
                qDebug()<<"ROBOT_STATE";
                GetRobotMessage(_data, offset, size);
                break;
            }
            case PROGRAM_STATE_MESSAGE:
            {
                break;
            }

            default:
                offset = size;
                break;
            }

        }
        _DataFlow = _DataFlow.mid(size);
       // MoveJ(QVector<double>({-0.5, -1.26, 1.21, -1.12, -1.76, 1.09}));
        mutex.unlock();
    }

}
void UR3Intermediator::CheckIfStillMovejRunning()
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
    QVector<double> target = QVector<double>
            ({RoundDouble(jointsData[0].getTargetJointPosition(),4),RoundDouble(jointsData[1].getTargetJointPosition(),4),
             RoundDouble(jointsData[2].getTargetJointPosition(),4),RoundDouble(jointsData[3].getTargetJointPosition(),4),
             RoundDouble(jointsData[4].getTargetJointPosition(),4),RoundDouble(jointsData[5].getTargetJointPosition(),4)});
    if(current == target)
    {
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
        emit newJointsPos(current);
    }

}

/*
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
        emit newPolozenie(current);
    }


}
*/

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

        switch(packageType){
        case ROBOT_MODE_DATA:
            this->ActualRobotInfo.setRobotModeData(_data, offset);
            break;
        case JOINT_DATA:
            this->ActualRobotInfo.setJointsData(_data, offset);
            if(_running)
            {
                CheckIfStillMovejRunning();
            }
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
            //CheckTCPChanged();
            break;
        case KINEMATICS_INFO:
            break;
        case CONFIGURATION_DATA:
            break;
        case FORCE_MODE_DATA:
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

QByteArray UR3Intermediator::ReadDataFlow()
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

bool UR3Intermediator::ConnectToRobot()
{

    if (_connected == false)
    {
        _socket->connectToHost(IpAddress,Port);
        if(_socket->waitForConnected())
        {
            _connected = true;
            return true;
        }
        else
        {
            _connected = false;
            return false;
        }
    }
    return true;


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
