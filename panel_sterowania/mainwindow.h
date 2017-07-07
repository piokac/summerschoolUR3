#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settings.h"
#include "UR3Intermediator.h"
#include "waypoint.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int getPole1() const;
    void setPole1(int value);

    QString getPole2() const;
    void setPole2(const QString &value);

signals:
    void moduleChanged(QObject *object);


public slots:
    void showConfigWindow();
    void OnNewTCP(QVector<double> data, char a);
    void OnActionConnection();
    void ConnectedToInfo(char* Ip, bool Achieved);
    void showSettings();
    void showWayPoint();

    void OnMoveJ();
    void OnSpeedJ();
    void OnForceMode();
    void onHome();
    void onServoc();


private slots:
    void on_actionConnection_triggered();

    void on_pushButton_MoveJ_clicked();

    void on_actionParameters_triggered();

private:
    WayPoint * wp;
    UR3Intermediator* ur3;
    Ui::MainWindow *ui;
    Settings *settings;
    Q_PROPERTY(QString pole2_test READ getPole2 WRITE setPole2 USER true)
    Q_PROPERTY(int pole1_test READ getPole1 WRITE setPole1 USER true)
    int pole1;
    QString pole2;


};

#endif // MAINWINDOW_H
