#ifndef UR3INTERMEDIATOR_H
#define UR3INTERMEDIATOR_H


#pragma once
#include <vector>
#include "UR3Message.h"
#include "UR3MessageOut.h"
#include <string>
#include <QObject>

using namespace std;

class UR3Intermediator: public QObject
{

public:
    Q_OBJECT
    bool Connect();

    vector<int> ReadDataFlow();

    bool SendData(string ParsedToStringMethod);
    string ParseOutput(UR3MessageOut MessageToSend);

    void LogData(string data);
    void ViewData();
    UR3Message DecipherMessage(const vector<int>& DataFlow);

    volatile vector<int> DataFlow;
signals:
    void newTCP(QVector<double> pose);





};


#endif // UR3INTERMEDIATOR_H
