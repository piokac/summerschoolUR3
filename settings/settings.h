/**
 * \file settings.h
 * \author Przemysław Maliński
 * \date 30.06.17
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QFile>
#include <settingswindow.h>
#include <QMetaObject>
#include <QMetaProperty>
#include <QMessageBox>

/**
 * \class Settings
 * \brief Klasa służy do zarządzania ustawieniami poszczególnych modułów.
 */

class Settings : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Settings - konstruktor domyślny klasy Settings
     * @param file - nazwa pliku zawierającego ustawienia
     * @param parent - parent klasy Settings
     */
    explicit Settings(const QString file, QObject *parent = 0);
    ~Settings();

    /**
     * @brief restoreBinary - metoda zwracająca ustawienia danego modułu z pliku binarnego
     * @param object - moduł, którego ustawienia są zwracane
     * @return - ustawienia modułu w postaci ciągu bajtów
     */
    QByteArray restoreBinary(QObject *object);
    /**
     * @brief serializeBinary - metoda zapisująca ustawienia danego modułu do pliku binarnego
     * @param object - moduł, którego ustawienia są zapisywane
     * @param data - ustawienia modułu w postaci ciągu bajtów
     * @return - informacja czy zapis przebiegł pomyślnie
     */
    bool serializeBinary(QObject *object, QByteArray data);
    /**
     * @brief read - metoda odczytująca ustawienia danego modułu
     * @param object - moduł, do którego zapisywane są ustawienia
     */
    void read(QObject *object);
    /**
     * @brief serialize - metoda zapisująca ustawienia danego modułu do pliku
     * @param object - moduł, którego ustawienia są zapisywane
     */
    void serialize(QObject *object);
    /**
     * @brief modify - metoda modyfikująca ustawienia danego modułu
     * @param object - moduł, którego ustawienia są modyfikowane
     */
    void modify(QObject *object);
    /**
     * @brief getWindow - getter okna ustawień
     * @return - wskaźnik na okno ustawień
     */
    SettingsWindow *getWindow();

signals:
    void settingsChanged();

public slots:
    /**
     * @brief saveSettings - slot zapisujący ustawienia po zatwierdzeniu okna dialogowego
     */
    void saveSettings();
    /**
     * @brief moduleChanged - slot zapisujący informację o aktualnie obsługiwanym module
     */
    void moduleChanged(QObject *object);

private:
    QObject *m_currentObject;///<wskaźnik na aktualny moduł
    SettingsWindow *m_window;///<wskaźnik na okno ustawień
    QSettings *m_settings;///<wskaźnik na zmienną przechowującą ustawienia wszystkich modułów
    QString m_filename;///<nazwa pliku zawierającego ustawienia
};

#endif // SETTINGS_H
