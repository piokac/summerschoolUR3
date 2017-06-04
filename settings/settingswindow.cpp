#include "settingswindow.h"
#include "ui_settingswindow.h"
#include <QDebug>

SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::on_buttonBox_accepted()
{
    emit settingsAccepted();
}

void SettingsWindow::setWindow(QObject *object)
{
    const QMetaObject *meta_object = object->metaObject();
    int ilosc_property = meta_object->propertyCount();
    int iloscUser = 0;
    QString className(meta_object->className()); //nazwa klasy

    for (int i = 0; i<ilosc_property; i++)
    {
        QMetaProperty metaProperty = meta_object->property(i);
        if (metaProperty.isWritable() && metaProperty.isUser()) //property zostaje zmienione jesli jest do zapisu
        {
            iloscUser++;
            //QString propertyName = metaProperty.name(); //nazwa property
            //QVariant value = metaProperty.read(object); //wartosc parametru
        }
    }
    ui->lineEdit_nazwa->setText(meta_object->className());
    ui->lineEdit_ilosc->setText(QString::number(ilosc_property));
    ui->lineEdit_iloscUser->setText(QString::number(iloscUser));
}
