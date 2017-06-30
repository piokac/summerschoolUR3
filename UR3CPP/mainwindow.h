#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "UR3Intermediator.h"
#include "connectdialog.h"

#include <QMainWindow>
#include "settings.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void moduleChanged(QObject *object);

private:

    Ui::MainWindow *ui;
    UR3Intermediator* ur3;
    ConnectDialog* connectDialog;

    Settings *settings;

public slots:


    void OnConnectedDialogInfo(QString ip, int port);
    void OnMoveJ();
    void OnSpeedJ();
    void OnMoveL();
    void OnSamuraiCut();
    void OnActionConnection();
    void Home();

    void OnNewJointPos(QVector<double> pose);
    void OnNewTCP(QVector<double> data, char c);
    void ConnectedToInfo(char* Ip, bool Achieved);

    void showSettings();

};

#endif // MAINWINDOW_H
