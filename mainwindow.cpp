#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGamepadManager>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::PadButtonPressed()
{
    auto gamepads = QGamepadManager::instance()->connectedGamepads();
    if (gamepads.isEmpty()) {
        return;
    }
    else
    {

    }
}



