#include "ccontrol.h"
#include <QDebug>

cControl::cControl(QObject *parent) : QObject(parent)
{

}

void cControl::update(UR3Message *state, const QTime &t)
{
    state_ = *state;
    //qDebug()<<"force: "<<state->forceModeData.getFZ()<< " force copied: "<<state_.forceModeData.getFZ();
}

cControlFTWC::cControlFTWC(QObject *parent)
{
    isChange = 0;
    FinalVec.resize(6);
}

void cControlFTWC::update(UR3Message *state,const QTime & t)
{
    if (isInitialized)
    {
        cControl::update(state,t);
        //      qDebug()<<"Module: "<<module;
        double Vx = (state->forceModeData.getFZ());
        //qDebug()<<"fabs(Vx - Vo): "<<fabs(Vx - module)<<" Fz:"<<state->forceModeData.getFZ();
        if (fabs(Vx - module) > 10) //narazie to tylko wartosci sil Fz
        {
            qDebug()<<"fabs(Vx - Vo): "<<(Vx - module);
            /*Fdiv.push_back(state->forceModeData.getFX() - bias[0]);
            Fdiv.push_back(state->forceModeData.getFY() - bias[1]);
            Fdiv.push_back(state->forceModeData.getFZ() - bias[2]);
            Fdiv.push_back(0 - bias[3]);
            double FdivModule = sqrt(pow(Fdiv[0], 2) + pow(Fdiv[1], 2) + pow(Fdiv[2], 2));
            V.push_back(Fdiv[0] / FdivModule);
            V.push_back(Fdiv[1] / FdivModule);
            V.push_back(Fdiv[2] / FdivModule);
            FinallyVec.push_back(state->cartesianInfoData.getX() + V[0] * 0.05);
            FinallyVec.push_back(state->cartesianInfoData.getY() + V[1] * 0.05);
            FinallyVec.push_back(state->cartesianInfoData.getZ() + V[2] * 0.05);
            FinallyVec.push_back(bias[4]);
            FinallyVec.push_back(bias[5]);
            FinallyVec.push_back(bias[6]);*/
            //     movep(currentTCP+z(50)*SIGN(Vx - module))
            FinalVec[0]=(state->cartesianInfoData.getX());
            FinalVec[1]=(state->cartesianInfoData.getY());
            FinalVec[2]=(state->cartesianInfoData.getZ()+50.0/1000*sign(Vx - module));
            FinalVec[3]=(state->cartesianInfoData.getRx());
            FinalVec[4]=(state->cartesianInfoData.getRy());
            FinalVec[5]=(state->cartesianInfoData.getRz());
            isChange = 3;
        }
        else
        {
            if(isChange&1)
            {
                FinalVec[0]=(state->cartesianInfoData.getX());
                FinalVec[1]=(state->cartesianInfoData.getY());
                FinalVec[2]=(state->cartesianInfoData.getZ()+0.0/1000*sign(Vx - module));
                FinalVec[3]=(state->cartesianInfoData.getRx());
                FinalVec[4]=(state->cartesianInfoData.getRy());
                FinalVec[5]=(state->cartesianInfoData.getRz());
                isChange = 2;
            }
        }
        //  module = sqrt(pow(state->forceModeData.getFX(),2) + pow(state->forceModeData.getFY(),2) + pow(state->forceModeData.getFZ(),2));
    }
}

QString cControlFTWC::getControl(const QTime &t)
{
    QString command;
    if(isChange&2)
    {
        double acceleration = 0.01;
        double speed = 0.01;
        command = "movep(p[" +
                QString::number(FinalVec[0]) + ", " +
                QString::number(FinalVec[1]) + ", " +
                QString::number(FinalVec[2]) + ", " +
                QString::number(FinalVec[3]) + ", " +
                QString::number(FinalVec[4]) + ", " +
                QString::number(FinalVec[5]) + "], " +
                "a=" + QString::number(acceleration)+ ", " +
                "v=" + QString::number(speed)+ ")\n";
        isChange &= 1;
        qDebug()<<command;
    }
    return command;
}

void cControlFTWC::setBias(UR3Message *state)
{
    bias.push_back(0);
    bias.push_back(0);
    bias.push_back(state->cartesianInfoData.getRx() * state->cartesianInfoData.getRy() * state->cartesianInfoData.getRz()* state->forceModeData.getFZ());
    bias.push_back(state->cartesianInfoData.getRx() * state->cartesianInfoData.getRy() * state->cartesianInfoData.getRz());
    bias.push_back(state->cartesianInfoData.getRx());
    bias.push_back(state->cartesianInfoData.getRy());
    bias.push_back(state->cartesianInfoData.getRz());
    isInitialized = 1;
    //module = sqrt(pow(state->forceModeData.getFX(),2) + pow(state->forceModeData.getFY(),2) + pow(state->forceModeData.getFZ(),2));
    module = (state->forceModeData.getFZ());
    //    qDebug()<<"Fx: "<<state->forceModeData.getFX()<<"Fy: "<<state->forceModeData.getFY()<<"Fz: "<<state->forceModeData.getFZ()<<"modul: "<<module;
}

int cControlFTWC::sign(int a)
{
    return a/fabs(a);
}

/*cProportionalIntegralController::cProportionalIntegralController(QObject *parent)
{
    kp = 0.005;
    ki = 0.005 / 2;
}*/

/*QString cProportionalIntegralController::getControl(const QTime &t)
{
    QString command;
    UR3Message * state;
    QTime &timer;
    update(state, timer);
    double fnorm = fabs(Vx - module) - 10;
    int_Ft += fnorm * t; //t jest typu QTime
    V = 0.01 + kp * fnorm + ki * int_Ft;

    if(isChange&2)
    {
        double acceleration = 0.01;
        command = "movep(p[" +
                QString::number(FinalVec[0]) + ", " +
                QString::number(FinalVec[1]) + ", " +
                QString::number(FinalVec[2]) + ", " +
                QString::number(FinalVec[3]) + ", " +
                QString::number(FinalVec[4]) + ", " +
                QString::number(FinalVec[5]) + "], " +
                "a=" + QString::number(acceleration)+ ", " +
                "v=" + QString::number(V)+ ")\n";
        isChange &= 1;
        qDebug()<<command;
    }
    return command;
}*/
