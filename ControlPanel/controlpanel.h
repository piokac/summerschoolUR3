#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H
#include <QMenu>
#include <QWidget>
#include "QMenuBar"
#include "dialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>


namespace Ui {
class controlpanel;
}

class controlpanel : public QWidget
{
    Q_OBJECT

public:
    explicit controlpanel(QWidget *parent = 0);
    ~controlpanel();

    void getSettings(Dialog* settingsDialog);
    void setBoxOK(QLabel* label);
    void setBoxNot(QLabel* label);

public slots:
    void showSettings();


private:
    Ui::controlpanel *ui;
    QWidget* p_checkbox;
};

#endif // CONTROLPANEL_H
