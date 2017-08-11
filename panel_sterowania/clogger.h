#ifndef CLOGGER_H
#define CLOGGER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QVector>
#include "UR3Intermediator.h"

class cLogger : public QObject
{
    Q_OBJECT
public:
    explicit cLogger(QObject *parent = 0);

    void Open(QString SaveFileName);
    void Close();
    void Open();

private:
    UR3Intermediator ur3;
    bool flag;
    QFile file;
    QTextStream stream;

public slots:
    void slot_turn(int devId, char id, QVector <double> vec);


};

#endif // CLOGGER_H
