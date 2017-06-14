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

void UR3Intermediator::GetRobotMessage(char *data, unsigned int &offset)
{
    int sizeOfPackage;
    memcpy(&sizeOfPackage, &data[offset], sizeof(sizeOfPackage));

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
