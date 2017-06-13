#include "UR3Intermediator.h"

#include <QHostAddress>

UR3Intermediator::UR3Intermediator():_connected(false),Port(30002),IpAddress("192.168.146.128")
{
    this->_socket = new QTcpSocket();
    connect(this->_socket,SIGNAL(readyRead()),this,SLOT(OnSocketNewBytesWritten()));
    ConnectToRobot();

}

void UR3Intermediator::GetRobotMessage( QByteArray &DataFlow)
{
    char * buffer = DataFlow.data();
    unsigned int offset = 0;
    int size;


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
