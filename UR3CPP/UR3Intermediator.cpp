#include "UR3Intermediator.h"

#include <QHostAddress>
char *strdup (const char *s)
{
    char* d = (char*)malloc(strlen (s) + 1);   // Space for length plus nul
    if (d == NULL) return NULL;          // No memory
    strcpy (d,s);                        // Copy the characters
    return d;                            // Return the new string
}
UR3Intermediator::UR3Intermediator():_connected(false),Port(30002),IpAddress("192.168.146.128")
{
    this->_socket = new QTcpSocket();
    connect(this->_socket,SIGNAL(readyRead()),this,SLOT(OnSocketNewBytesWritten()));
    ConnectToRobot();

}

void UR3Intermediator::GetRobotData()
{
    int size = 0;
    unsigned int offset = 0;
    memcpy(&size, &_data[offset], sizeof(size));
    offset += sizeof(size);
    while(offset<size)
    {
        unsigned char Type;
        memcpy(&Type,&_data[offset],sizeof(Type));
        offset+=sizeof(Type);
        int messageType = Type - '0';
        switch(messageType)
        {
            case ROBOT_MESSAGE:
            {
                GetRobotMessage(_data, offset, size);
                break;
            }
            case ROBOT_STATE:
            {
                break;
            }
            case PROGRAM_STATE_MESSAGE:
            {
                break;
            }

            default:
                break;
        }

    }



}

void UR3Intermediator::GetRobotMessage(char *data, unsigned int &offset, int size)
{
    while(size>offset){
        int sizeOfPackage;
        memcpy(&sizeOfPackage, &data[offset], sizeof(sizeOfPackage));
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
                this->ActualRobotInfo->setCartesianInfoData(_data,offset);
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

        if(_socket->waitForReadyRead())
        {
            this->_socket->waitForReadyRead();
             QByteArray data = this->_socket->readAll();
            _DataFlow = data;
            auto xd = data.data(); // dlaczego pokazuje sie puste
            _data = strdup(data.data());

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

void UR3Intermediator::OnTcpChanged()
{

}

void UR3Intermediator::OnSocketNewBytesWritten()
{
    this->ReadDataFlow();
}
