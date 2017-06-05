#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include <QMetaObject>
#include <QMetaProperty>
#include <QSettings>

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
     * @brief setWindow Metoda tworząca layout okna ustawień.
     * @param object    Obiekt, którego ustawienia są wyświetlane.
     */
    void setWindow(QObject *object);

signals:
    /**
     * @brief settingsAccepted Sygnał o zaakceptowaniu zmian w ustawieniach.
     */
    void settingsAccepted();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SettingsWindow *ui;
};

#endif // SETTINGSWINDOW_H
