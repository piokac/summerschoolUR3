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
    void OnNewJointPos(QVector<double> pose);
    //void OnNewTCP(QVector<double> tcp);

};

#endif // MAINWINDOW_H
