#ifndef MYOFORM_H
#define MYOFORM_H

#include <QWidget>

namespace Ui {
class MYOForm;
}

class MYOForm : public QWidget
{
    Q_OBJECT

public:
    explicit MYOForm(QWidget *parent = 0);
    ~MYOForm();


private slots:
    void on_pushButton_connect_clicked();
    void gestureChanged(QString type);
signals:
    void connectMyo();
private:
    Ui::MYOForm *ui;
};

#endif // MYOFORM_H
