#include "myoform.h"
#include "ui_myoform.h"

MYOForm::MYOForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MYOForm)
{
    ui->setupUi(this);
}

MYOForm::~MYOForm()
{
    delete ui;
}

void MYOForm::gestureChanged(QString type)
{
    ui->lineEdit_gesture->setText(type);
}

void MYOForm::on_pushButton_connect_clicked()
{
    emit connectMyo();
}
