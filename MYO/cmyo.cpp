#include "cmyo.h"

cMYO::cMYO(UR3Intermediator* robot, QObject *parent) : m_robot(robot),QObject(parent)
{

    //connect(m_robot,SIGNAL(newTCP(QVector<double>))
    widget = new MYOForm;
    connect(this, SIGNAL(nowyGest(QString)), widget, SLOT(gestureChanged(QString)));
    connect(widget,SIGNAL(connectMyo()), this, SLOT(polacz_z_myo()));
}

QWidget *cMYO::getWidget()
{
    return widget;
}

QString cMYO::getIP() const
{
    return m_IP;
}

void cMYO::setIP(const QString &IP)
{
    m_IP = IP;
}
