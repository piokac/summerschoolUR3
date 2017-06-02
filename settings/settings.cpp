#include "settings.h"
#include <QDebug>
#include <QSettings>
#include <QFile>

Settings::Settings(QObject *parent) : QObject(parent)
{
    Parameters = new UR3Parameters; //przydzielenie pamieci dla parametrow
    Properties = new QSettings("properties.ini", QSettings::IniFormat); //przydzielenie pamieci dla wlasciwosci (zapis do pliku properties.ini)

    //PARAMETRY TESTOWE (TYMCZASOWE)
    Parameters->zmiennaBool = true;
    Parameters->zmiennaChar = 'a';
    Parameters->zmiennaInt = 1;
    Parameters->zmiennaFloat = 3.14159265359F;
    for (int i = 0; i<5;i++)
    {
        Parameters->piecIntow[i] = i+1;
    }
    QString slowo("test123");
    if (slowo.size()>=10)
    {
        slowo.resize(9);
        slowo[9] = '\0';
    }
    else slowo.append('\0');
    qstrcpy(Parameters->slowo, slowo.toLatin1().data());

    propertiesBinary = new QFile("parameters.bin");
    setBinary(propertiesBinary);

    //WLASCIWOSCI
    if ((!QFile("properties.ini").exists()) || QFile("properties.ini").size()==0) //jesli plik konfiguracyjny nie istnieje to zostaje utworzony i uzupelniony wartosciami domyslnymi
    {
        //WLASCIWOSCI TESTOWE (TYMCZASOWE)
        Properties->beginGroup("ur3cpp");
        Properties->setValue("ipaddress", "192.168.100.100");
        Properties->endGroup();

        Properties->beginGroup("kalibracja");
        Properties->setValue("parametrXYZ", 123);
        Properties->endGroup();

        Properties->beginGroup("gamepad");
        Properties->setValue("padPodlaczony", true);
        Properties->endGroup();

        Properties->beginGroup("myo");
        Properties->setValue("myoTest", false);
        Properties->endGroup();

        Properties->beginGroup("polyline2ur");
        Properties->setValue("lines", 5);
        Properties->endGroup();

        Properties->beginGroup("text2keyboard");
        Properties->setValue("text", "test123");
        Properties->endGroup();

        Properties->beginGroup("controlpanel");
        Properties->setValue("panelIsOpened", true);
        Properties->endGroup();

        Properties->beginGroup("wizualizacja");
        Properties->setValue("isMoving", false);
        Properties->endGroup();
    }
}

Settings::~Settings()
{
    delete Parameters;
    delete Properties;
    delete propertiesBinary;
}

QFile *Settings::getBinary()
{
    return propertiesBinary;
}

void Settings::setBinary(QFile *binary) //zapis parametrow do pliku binarnego
{
    binary->open(QIODevice::WriteOnly);
    binary->write(reinterpret_cast<char*>(Parameters), sizeof(UR3Parameters));
    binary->close();
}

void Settings::Read(QObject* object)
{

}

void Settings::Serialize(QObject* object)
{

}

void Settings::Modify(QObject *object)
{

}
