#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <QDialog>
#include<qdebug.h>
#include<qlabel.h>
#include"macierz.h"


namespace Ui {
class WayPoint;
}



class WayPoint : public QDialog
{
    Q_OBJECT

public:
    explicit WayPoint(QWidget *parent = 0);
    ~WayPoint();

    double getWx() const;
    void setWx(double value);

    double getWy() const;
    void setWy(double value);

    double getWz() const;
    void setWz(double value);

    double getWrx() const;
    void setWrx(double value);

    double getWry() const;
    void setWry(double value);

    double getWrz() const;
    void setWrz(double value);

    double getA() const;
    void setA(double value);

    double getV() const;
    void setV(double value);

    void PushButtonData(QVector<double> data);

    QVector<double> getPose();
    void setPose(QVector<double> v);

    void SetText(QString text);

private slots:
    void on_pushButton_Ap_pressed();

    void selectSettings(QVector<double> &v_punkt);

    void on_pushButton_Ap_clicked();

private:
    Ui::WayPoint *ui;
    Macierz *M;
    double Wx, Wy, Wz;
    double Wrx, Wry, Wrz;
    double V, a;
    bool flaga;

};

#endif // WAYPOINT_H
