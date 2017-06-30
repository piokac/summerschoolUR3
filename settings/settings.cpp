#include "settings.h"
#include <QDebug>
#include <QSettings>
#include <QFile>

Settings::Settings(const QString file, QObject *parent):QObject(parent),
    m_currentObject(NULL), m_window(new SettingsWindow),
    m_filename(file), m_settings(new QSettings(file, QSettings::IniFormat))
{
    connect(m_window, SIGNAL(settingsAccepted()), this, SLOT(saveSettings())); //sygnal o zaakaceptowaniu okna ustawien = zapisanie ustawien
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
    bool skonfigurowano = true;
    for (int i = 0; i<ilosc_property; i++)
    {
        QMetaProperty metaProperty = meta_object->property(i);
        if (metaProperty.isUser()) //property zostaje zmienione jesli jest typu user
        {
            QString propertyName = metaProperty.name(); //nazwa property
            m_settings->beginGroup(className);
            if (!m_settings->value(propertyName).isNull()) //sprawdzenie czy dany klucz istnieje (wazne przy pierwszym uruchomieniu)
            {
                object->setProperty(propertyName.toLatin1().data(), m_settings->value(propertyName)); //zapisanie ustawien do obiektu
            }
            else
            {
                m_settings->setValue(propertyName, metaProperty.read(object));
                skonfigurowano = false;
            }
            m_settings->endGroup();
        }
    }
    if (!skonfigurowano) //wyswietlenie okna informujacego o koniecznosci skonfigurowania danego modulu
    {
        QMessageBox::information(0, className, "Moduł " + className + " wymaga konfiguracji."); //okno dialogowe komunikujace o koniecznosci konfiguracji ustawien
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
    const QMetaObject *meta_object = object->metaObject();
    int ilosc_property = meta_object->propertyCount();
    QString className(meta_object->className()); //nazwa klasy
    for (int i = 0; i<ilosc_property; i++)
    {
        QMetaProperty metaProperty = meta_object->property(i);
        if (metaProperty.isUser()) //property zostaje zmienione jesli jest typu user
        {
            QString propertyName = metaProperty.name(); //nazwa property
            QVariant value = m_settings->value(className + "/" + propertyName); //wartosc parametru

            if(QString::compare(QString::fromLatin1(metaProperty.typeName()), "bool") == 0) //konwersja na bool
            {
                value = value.toBool();
            }
            else if(QString::compare(QString::fromLatin1(metaProperty.typeName()), "int") == 0) //konwersja na int
            {
                value = value.toInt();
            }
            else if(QString::compare(QString::fromLatin1(metaProperty.typeName()), "float") == 0) //konwersja na float
            {
                value = value.toFloat();
            }
            else if(QString::compare(QString::fromLatin1(metaProperty.typeName()), "double") == 0) //konwersja na double
            {
                value = value.toDouble();
            }
            else //konwersja na QString
            {
                value = value.toString();
            }
            object->setProperty(propertyName.toLatin1().data(), m_settings->value(className + "/" + propertyName)); //zapisanie ustawien do obiektu
        }
    }
    emit settingsChanged(); //emitowanie sygnalu o zmianie ustawien
}

SettingsWindow *Settings::getWindow()
{
    QString className(m_currentObject->metaObject()->className());
    m_window->setWindow(m_settings, className);
    return m_window;
}

void Settings::saveSettings()
{
    modify(m_currentObject);
}

void Settings::moduleChanged(QObject *object)
{
    if (m_currentObject != object)
    {
        m_currentObject = object;
    }
}
