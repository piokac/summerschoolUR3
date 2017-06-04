#include "settings.h"
#include <QDebug>
#include <QSettings>
#include <QFile>

Settings::Settings(const QString file, QObject *parent):QObject(parent),
    m_currentObject(NULL), m_window(new SettingsWindow),
    m_filename(file), m_settings(new QSettings(file, QSettings::IniFormat))
{
    connect(m_window, SIGNAL(settingsAccepted()), this, SLOT(saveSettings())); //sygnal o zaakaceptowaniu okna ustawien = zapisanie ustawien

    /*if ((!QFile(file).exists()) || QFile(file).size()==0) //tworzenie pliku z wartosciami domyslnymi (gdy plik ustawien nie istnieje)
    {
        m_settings->beginGroup("cGamepad");
        m_settings->endGroup();

        m_settings->beginGroup("cMYO");
        m_settings->endGroup();

        m_settings->beginGroup("polyline2ur3");
        m_settings->endGroup();

        m_settings->beginGroup("UR3CPP");
        m_settings->endGroup();

        m_settings->beginGroup("kalibracja");
        m_settings->endGroup();

        m_settings->beginGroup("text2keyboard");
        m_settings->endGroup();

        m_settings->beginGroup("controlpanel");
        m_settings->endGroup();

        m_settings->beginGroup("wizualizacja");
        m_settings->endGroup();
    }*/
}

Settings::~Settings()
{
    delete m_settings;
    delete m_window;
}

QByteArray Settings::restoreBinary(QObject *object)
{
    return 0;
}

bool Settings::serializeBinary(QObject *object, QByteArray data)
{
    return false;
}

void Settings::read(QObject *object) //zapisuje ustawienia do modulu
{
    const QMetaObject *meta_object = object->metaObject();
    int ilosc_property = meta_object->propertyCount();
    QString className(meta_object->className()); //nazwa klasy
    for (int i = 0; i<ilosc_property; i++)
    {
        QMetaProperty metaProperty = meta_object->property(i);
        if (metaProperty.isWritable() && metaProperty.isUser()) //property zostaje zmienione jesli jest do zapisu
        {
            QString propertyName = metaProperty.name(); //nazwa property
            QVariant value = m_settings->value(className + "/" + propertyName); //wartosc parametru
            object->setProperty(propertyName.toLatin1().data(), m_settings->value(className + "/" + propertyName)); //zapisanie ustawien do obiektu
        }
    }
}

void Settings::serialize(QObject *object) //zapisuje ustawienia modulu do pliku
{
    const QMetaObject *meta_object = object->metaObject();
    int ilosc_property = meta_object->propertyCount();
    QString className(meta_object->className()); //nazwa klasy
    for (int i = 0; i<ilosc_property; i++)
    {
        QMetaProperty metaProperty = meta_object->property(i);
        if(metaProperty.isUser())
        {
            QString propertyName = metaProperty.name(); //nazwa property
            QVariant value = metaProperty.read(object); //wartosc parametru
            m_settings->setValue(className + "/" + propertyName, value); //zapisanie ustawien do pliku
        }
    }
}

void Settings::modify(QObject *object) //modyfikuje ustawienia modułu
{
    //pobranie informacji z okna ustawien, zapisanie je do QSettings
    read(object); //przekazanie ustawień do modułu
}

SettingsWindow *Settings::getWindow()
{
    m_window->setWindow(m_currentObject);
    return m_window;
}

void Settings::saveSettings()
{
    this->modify(m_currentObject);
}

void Settings::moduleChanged(QObject *object)
{
    if (m_currentObject != object)
    {
        m_currentObject = object;
    }
}
