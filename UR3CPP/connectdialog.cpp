#include "connectdialog.h"
#include "ui_connectdialog.h"

ConnectDialog::ConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);
    connect(this->ui->pushButton_Connect,SIGNAL(clicked(bool)),this,SLOT(ConnectButtonClicked()));
}

ConnectDialog::~ConnectDialog()
{
    delete ui;
}

void ConnectDialog::ConnectButtonClicked()
{
    QString adr = ui->lineEdit_Adress->text();
    int port = ui->lineEdit_2->text().toInt();
    emit ConnectClicked(adr,port);
    this->close();
}
