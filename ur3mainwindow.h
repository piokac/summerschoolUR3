#ifndef UR3MAINWINDOW_H
#define UR3MAINWINDOW_H

#include <QMainWindow>

#include <settings.h>
#include <UR3Intermediator.h>
#include  <cmyo.h>
namespace Ui {
class UR3MainWindow;
}

class UR3MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UR3MainWindow(QWidget *parent = 0);
    ~UR3MainWindow();

private:
    Ui::UR3MainWindow *ui;
    Settings* ustawienia;
    UR3Intermediator* robot;
    cMYO* myo;

};

#endif // UR3MAINWINDOW_H
