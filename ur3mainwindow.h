#ifndef UR3MAINWINDOW_H
#define UR3MAINWINDOW_H

#include <QMainWindow>

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
};

#endif // UR3MAINWINDOW_H
