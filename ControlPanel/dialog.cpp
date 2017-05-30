#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


bool Dialog::getData(QCheckBox *przycisk)
{
    if(przycisk->isChecked())
        return true;
    return false;
}
bool Dialog::giveVoltage()
{
    return getData(ui->voltageBox);
}
bool Dialog::giveCurrentdc()
{
    return getData(ui->currentBox);
}
bool Dialog::giveTemperature()
{
    return getData(ui->temperatureBox);
}
bool Dialog::givePower()
{
    return getData(ui->powerBox);
}
bool Dialog::giveX()
{
    return getData(ui->xBox);
}
bool Dialog::giveY()
{
    return getData(ui->yBox);
}
bool Dialog::giveZ()
{
    return getData(ui->zBox);
}



void Dialog::on_OKButton_clicked()
{
    close();
}
