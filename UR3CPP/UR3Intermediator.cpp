#include "UR3Intermediator.h"
#include <QtGlobal>
#include <QtCore>
#include <QtEndian>
#include <QHostAddress>
#include <QDebug>
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


UR3Intermediator::UR3Intermediator():_connected(false),Port(30002),IpAddress("192.168.146.128")
{
    this->_socket = new QTcpSocket();
    qDebug()<<"UR3Intermediator::UR3Intermediator()";
    connect(this->_socket,SIGNAL(readyRead()),this,SLOT(OnSocketNewBytesWritten()));
    connect(this->_socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    ConnectToRobot();

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
            //if(_DataFlow.size()>=offset+sizeof(Type))
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
               // offset += xxB;
                break;
            }
            case PROGRAM_STATE_MESSAGE:
            {
                //offset += xxB;
                break;
            }

            default:
                offset = size;
                break;
            }

        }
        _DataFlow = _DataFlow.mid(size);
        mutex.unlock();
    }

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

        switch(packageType){
        case ROBOT_MODE_DATA:
            break;
        case JOINT_DATA:
            break;
        case TOOL_DATA:
            break;
        case MASTERBOARD_DATA:
            break;
        case CARTESIAN_INFO:
            this->ActualRobotInfo.setCartesianInfoData(_data,offset);
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

        // if(_socket->waitForReadyRead())
        {
            // this->_socket->waitForReadyRead();
            if(mutex.tryLock())
            {
                _DataFlow.push_back( this->_socket->readAll());

                mutex.unlock();
            }

            //            const char* xd = (const char*)data.data(); // dlaczego pokazuje sie puste
            //            _data = _DataFlow.data();

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
        }
        else
        {
            _connected = false;
            return false;
        }
    }


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
