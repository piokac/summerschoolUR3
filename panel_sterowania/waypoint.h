#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <QDialog>
#include<qdebug.h>
#include<qlabel.h>
#include"macierz.h"

namespace Ui {
class WayPoint;
}
/**
 * @brief The WayPoint class - okienko służące do pobierania punktu drogi dla robota
 */
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
    /**
     * @brief PushButtonData - po naciśnięciu przycisku "Actual Position" wypełnianie pól edytowalnych współrzędnymi robota
     * @param data - dane z robota
     */
    void PushButtonData(QVector<double> data);
    /**
     * @brief PushButtonDataCC - po naciśnięciu przycisku "Configuration Coordinates" wypełnianie pól edytowalnych współrzędnymi robota we współrzędnych konfiguracyjnych
     * @param data - dane z robota
     */
    void PushButtonDataCC(QVector<double>data);   
    /**
     * @brief getPose - pobieranie danych z pól edytowalnych i zapisywanie ich w wektorze
     * @return - wektor z danymi pobranymi z pól
     */
    QVector<double> getPose();
    /**
     * @brief SetText - ustawienie opisu okienka
     * @param text - opis
     */
    void SetText(QString text);
    /**
     * @brief setTransformation - ustawienie macierzy transformacji obiektu klasy macierz
     * @param v
     */
    void setTransformation(QVector<QVector<double> > v);
    QVector<QVector<double>> getTransformation();
    /**
     * @brief setInvTransformation - ustawienie macierzy odwrotnej transformacji obiektu klasy macierz
     * @param v
     */
    void setInvTransformation(QVector<QVector<double> > v);

private slots:
    /**
     * @brief on_pushButton_Ap_pressed - naciśnięcie przycisku "Actual Position"
     */
    void on_pushButton_Ap_pressed();
    /**
     * @brief on_pushButton_Ap_clicked - kliknięcie przycisku "Actual Position"
     */
    void on_pushButton_Ap_clicked();
    /**
     * @brief on_pushButton_cc_pressed - naciśnięcie przycisku "Configuration Coordinates"
     */
    void on_pushButton_cc_pressed();
    /**
     * @brief on_pushButton_cc_clicked - kliknięcie przycisku "Configuration Coordinates"
     */
    void on_pushButton_cc_clicked();

private:
    Ui::WayPoint *ui;
    Macierz *M;
    double Wx;/*!<zmienna skojarzona z polem X line edit */
    double Wy;/*!<zmienna skojarzona z polem Y line edit */
    double Wz;/*!<zmienna skojarzona z polem Z line edit */
    double Wrx;/*!<zmienna skojarzona z polem Rx line edit */
    double Wry;/*!<zmienna skojarzona z polem Ry line edit */
    double Wrz;/*!<zmienna skojarzona z polem Rz line edit */
    double V;/*!<zmienna skojarzona z polem V line edit */
    double a;/*!<zmienna skojarzona z polem a line edit */
    bool flaga;/*!<flaga reagująca na przycisk "Actual Position" */
    bool plFlag;/*!<flaga reagująca na przycisk "Configuration Coordinates" */
};

#endif // WAYPOINT_H
