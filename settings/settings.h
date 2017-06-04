#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QFile>
#include <settingswindow.h>
#include <QMetaObject>
#include <QMetaProperty>

class Settings : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Settings  Konstruktor domyślny klasy Settings.
     * @param file      Nazwa pliku zawierającego ustawienia.
     * @param parent    Parent klasy Settings.
     */
    explicit Settings(const QString file, QObject *parent = 0);
    ~Settings();

    /**
     * @brief restoreBinary Metoda zwracająca ustawienia danego modułu.
     * @param object        Moduł, którego ustawienia są zwracane.
     * @return              Ustawienia modułu w postaci ciągu bajtów.
     */
    QByteArray restoreBinary(QObject *object);
    /**
     * @brief serializeBinary   Metoda zapisująca ustawienia danego modułu do pliku binarnego.
     * @param object            Moduł, którego ustawienia są zapisywane.
     * @param data              Ustawienia modułu w postaci ciągu bajtów.
     * @return                  Informacja czy zapis przebiegł pomyślnie.
     */
    bool serializeBinary(QObject *object, QByteArray data);
    /**
     * @brief read      Metoda odczytująca ustawienia danego modułu.
     * @param object    Moduł, do którego zapisywane są ustawienia.
     */
    void read(QObject *object);
    /**
     * @brief serialize Metoda zapisująca ustawienia danego modułu do pliku.
     * @param object    Moduł, którego ustawienia są zapisywane.
     */
    void serialize(QObject *object);
    /**
     * @brief modify    Metoda modyfikująca ustawienia danego modułu.
     * @param object    Moduł, którego ustawienia są modyfikowane.
     */
    void modify(QObject *object);
    /**
     * @brief getWindow Getter okna ustawień.
     * @return          Wskaźnik na okno ustawień.
     */
    SettingsWindow *getWindow();

signals:

public slots:
    /**
     * @brief saveSettings Slot zapisujący ustawienia po zatwierdzeniu okna dialogowego.
     */
    void saveSettings();
    /**
     * @brief moduleChanged Slot zapisujący informację jaki moduł jest aktualnie obsługiwany.
     * @param object
     */
    void moduleChanged(QObject *object);

private:
    QObject *m_currentObject;///<Wskaźnik na aktualny moduł.
    SettingsWindow *m_window;///<Wskaźnik na okno ustawień.
    QSettings *m_settings;///<Wskaźnik na zmienną przechowującą ustawienia wszystkich modułów.
    QString m_filename;///<Nazwa pliku zawierającego ustawienia.
};

#endif // SETTINGS_H
