#ifndef CCONTROL_H
#define CCONTROL_H

#include <QObject>
#include "UR3Message.h"


class cControl : public QObject
{
    Q_OBJECT
public:

    explicit cControl(QObject *parent = 0);

    virtual void update (UR3Message * state, const QTime& t);
    //virtual QVector <double> getControl (const QTime& t) = 0;
    virtual QString getControl (const QTime& t) = 0;
    virtual void setBias(UR3Message *state) = 0;

private:
    UR3Message state_;


};

class cControlFTWC: public cControl
{
    Q_OBJECT
public:

    explicit cControlFTWC(QObject *parent = 0);

    void update (UR3Message * state, const QTime& t);
    QString getControl(const QTime& t);
    void setBias(UR3Message *state);
    int sign(int a);


private:
    QVector <double> bias;
    QVector <double> Fdiv;
    QVector <double> V;
    QVector <double> FinalVec;
    bool isInitialized;
    double module;
    int isChange;

};

/*class cProportionalIntegralController: public cControlFTWC
{
    Q_OBJECT
public:

    explicit cProportionalIntegralController(QObject *parent = 0);

    QString getControl(const QTime& t);

private:
    double kp, ki;
    double int_Ft;
};*/

#endif // CCONTROL_H
