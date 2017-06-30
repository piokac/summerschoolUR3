/**
 * \file settingswindow.h
 * \author Przemysław Maliński
 * \date 30.06.17
 */

#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include <QMetaObject>
#include <QMetaProperty>
#include <QSettings>
#include <QVector>
#include <QLineEdit>
#include <QPair>
#include <QLabel>

/**
 * \class SettingsWindow
 * \brief Klasa służy do tworzenia okna ustawień, wyświetlania go i przekazywania wartości wprowadzonych przez użytkownika do ustawień.
 */

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = 0);
    ~SettingsWindow();
    /**
     * @brief setWindow - metoda tworząca layout okna ustawień
     * @param settings - klasa zawierająca ustawienia modułów
     * @param className - nazwa aktualnie obsługiwanej klasy
     */
    void setWindow(QSettings *settings, QString className);

signals:
    /**
     * @brief settingsAccepted - sygnał o zaakceptowaniu zmian w ustawieniach
     */
    void settingsAccepted();

private slots:
    /**
     * @brief on_buttonBox_accepted - slot wciśnięcia przycisku "OK" w panelu ustawień
     */
    void on_buttonBox_accepted();

private:
    Ui::SettingsWindow *ui;
    QWidget *settingsWidget; ///<wskaźnik na widget ustawień
    QString currentClassName; ///<nazwa aktualnie obsługiwanej klasy
    QSettings *m_settings; ///<wskaźnik na ustawienia
    QVector<QPair<QLabel*, QLineEdit*>> widgetsList; ///<wektor wskaźników do dynamicznie stworzonych widgetów
};

#endif // SETTINGSWINDOW_H
