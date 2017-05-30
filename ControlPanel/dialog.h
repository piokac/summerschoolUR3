#ifndef DIALOG_H
#define DIALOG_H
#include <QCheckBox>
#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    bool giveVoltage();
    bool giveTemperature();
    bool giveCurrentdc();
    bool givePower();
    bool giveX();
    bool giveY();
    bool giveZ();

private slots:
    void on_OKButton_clicked();

private:
    Ui::Dialog *ui;
    bool voltage;
    bool temperature;
    bool currentdc;
    bool power;
    bool X;
    bool Y;
    bool Z;
    bool getData(QCheckBox* przycisk);
};

#endif // DIALOG_H
