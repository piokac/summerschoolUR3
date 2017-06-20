#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qvector>
#include "cgamepad.h"
#include <QDebug>


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
   // void move_vector(vector<double> tmp);

private slots:
    void PadButtonPressed();
    void MoveThumbstick();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
