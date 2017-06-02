#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QFile>

struct UR3Parameters //struktura zawierajaca paramtery
{
    char zmiennaChar;
    bool zmiennaBool;
    char slowo[10];
    int zmiennaInt;
    float zmiennaFloat;
    int piecIntow[5];
};

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = 0);
    ~Settings();
    /**
     * @brief getBinary
     * @return
     */
    QFile* getBinary(); //getter wskaznika do pliku binarnego
    void setBinary(QFile* binary); //funkcja zapisujaca parametry do pliku binarnego

    void Read(QObject* object);
    void Serialize(QObject* object);
    void Modify(QObject* object);

signals:

public slots:

private:
    UR3Parameters *Parameters; //wskaznik do parametrow
    QSettings *Properties; //wskaznik do wlasciwosci
    QFile* propertiesBinary; //wskaznik do pliku

};

#endif // SETTINGS_H
