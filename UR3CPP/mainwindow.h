#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "UR3Intermediator.h"
#include "connectdialog.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:

    Ui::MainWindow *ui;
    UR3Intermediator* ur3;
    ConnectDialog* connectDialog;

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

};

#endif // MAINWINDOW_H
