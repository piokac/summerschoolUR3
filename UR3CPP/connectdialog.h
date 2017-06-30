#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDialog(QWidget *parent = 0);
    ~ConnectDialog();
signals:
    ConnectClicked(QString ip,int port);
private slots:
    void ConnectButtonClicked();
private:

    Ui::ConnectDialog *ui;
};

#endif // CONNECTDIALOG_H
