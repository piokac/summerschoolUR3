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

    /**
     * @brief Open - Otwarcie wybranego pliku
     * @param SaveFileName - Ścieżka do pliku
     */
    void Open(QString SaveFileName);
    /**
     * @brief Close - Wstrzymanie zapisu
     */
    void Close();
    /**
     * @brief Open - Wznowienie zapisu
     */
    void Open();

private:
    UR3Intermediator ur3;
    bool flag; //< Flaga wstrzymująca / wznawiająca zapisywanie
    QFile file;
    QTextStream stream;

public slots:
    /**
     * @brief slot_turn - Przekazanie danych
     * @param devId
     * @param id
     * @param vec
     */
    void slot_turn(int devId, char id, QVector <double> vec);


};

#endif // CLOGGER_H
