#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settings.h"
#include "UR3Intermediator.h"

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

public slots:
    void showConfigWindow();

private:
    Ui::MainWindow *ui;
    Settings *settings;
    Q_PROPERTY(QString pole2_test READ getPole2 WRITE setPole2 USER true)
     Q_PROPERTY(int pole1_test READ getPole1 WRITE setPole1 USER true)
    int pole1;
    QString pole2;
    UR3Intermediator* ur3;
};

#endif // MAINWINDOW_H
