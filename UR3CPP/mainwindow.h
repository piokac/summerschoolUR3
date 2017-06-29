#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "UR3Intermediator.h"

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

public slots:
    void OnActionConnection();
    void OnNewJointPos(QVector<double> pose);
    void OnNewTCP(QVector<double> data, char c);
    void ConnectedToInfo(char* Ip, bool Achieved);

};

#endif // MAINWINDOW_H
