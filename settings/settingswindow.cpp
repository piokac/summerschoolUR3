#include "settingswindow.h"
#include "ui_settingswindow.h"
#include <QDebug>

SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent), settingsWidget(NULL), m_settings(NULL),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Ustawienia");
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
    delete settingsWidget;
}

void SettingsWindow::setWindow(QSettings *settings, QString className)
{
    if (settingsWidget != NULL)
    {
        delete settingsWidget;
        widgetsList.clear();
    }
    settingsWidget = new QWidget(this); //tworzenie widgetu ustawien
    QGridLayout *grid = new QGridLayout(settingsWidget);
    settingsWidget->setLayout(grid);

    currentClassName = className;
    m_settings = settings;

    settings->beginGroup(className);
    QStringList keys = settings->allKeys();
    this->setWindowTitle("Ustawienia modułu " + className);

    for(int i = 0; i < keys.size(); i++)
    {
        QLabel *label = new QLabel(settingsWidget); //tworzony jest label opisujacy dane ustawienie
        label->setText(keys[i]);
        grid->addWidget(label, i, 0);
        QLineEdit *lineEdit = new QLineEdit(settingsWidget); //tworzony jest lineEdit umozliwiajacy zmiane wartosci ustawienia
        lineEdit->setText(settings->value(keys[i]).toString());
        grid->addWidget(lineEdit, i, 1);
        QPair<QLabel*, QLineEdit*> temp(label, lineEdit);
        widgetsList.push_back(temp); //zapisanie wskaznikow na widgety stworzone dynamicznie
    }
    settings->endGroup();
    ui->verticalLayout->addWidget(settingsWidget); //dodanie layoutu z widgetami do okna ustawien
}

void SettingsWindow::on_buttonBox_accepted()
{
    for (int i = 0; i < widgetsList.size(); i++)
    {
        QString key = currentClassName + "/" + widgetsList[i].first->text();
        QVariant value = widgetsList[i].second->text();
        m_settings->setValue(key, value);
    }
    emit settingsAccepted();
}
