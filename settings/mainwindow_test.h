#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include "settings.h"
#include "settingswindow.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QObject *getCurrentModule() const; //getter wskaznika do aktualnie uzywanego obiektu

    //settery i gettery zmiennych
    bool getZmiennaBool() const;
    void setZmiennaBool(bool value);

    int getZmiennaInt() const;
    void setZmiennaInt(int value);

    QString getIP() const;
    void setIP(const QString &value);

    double getZmiennaDouble() const;
    void setZmiennaDouble(double value);

signals:
    void currentModuleChanged(QObject*); //sygnał o zmianie aktualnego modułu (POTRZEBNY W CONTROL PANELU)

private slots:
    void showSettings(); //slot wlaczajacy okno ustawien
    void update();

private:
    Q_PROPERTY(QString adresIP READ getIP WRITE setIP USER true)
    Q_PROPERTY(bool stanBool READ getZmiennaBool WRITE setZmiennaBool USER true)
    Q_PROPERTY(int liczbaInt READ getZmiennaInt WRITE setZmiennaInt USER true)
    Q_PROPERTY(double liczbaDouble READ getZmiennaDouble WRITE setZmiennaDouble USER true)

    Ui::MainWindow *ui;

    Settings *ustawienia;

    //przykladowe zmienne
    bool zmiennaBool;
    int zmiennaInt;
    double zmiennaDouble;
    QString IP;

    QObject *currentModule;
};

#endif // MAINWINDOW_H
