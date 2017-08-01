#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>

#define _USE_MATH_DEFINES


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),settings(new Settings("settings.ini", this)), ur3(new UR3Intermediator), wp(new WayPoint), log(new cLogger),//ur3(new UR3Intermediator(this)), wp(new WayPoint(this)), log(new cLogger(this)),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this->ui->actionConnection,SIGNAL(triggered(bool)),this,SLOT(OnActionConnection()));
    connect(this->ui->actionDisconnection,SIGNAL(triggered(bool)),this,SLOT(OnActionDisconnection()));
    connect(this->ur3, SIGNAL(newPoseTCP(QVector<double>,char)),this, SLOT(OnNewTCP(QVector<double>,char)));
    connect(this->ur3,SIGNAL(ConnectionAction(char*,bool)),this,SLOT(ConnectedToInfo(char*,bool)));
    connect(ui->actionUstawienia_okna,SIGNAL(triggered(bool)),this,SLOT(showConfigWindow()));
    connect(this->ui->pushButton_MoveJ,SIGNAL(clicked(bool)),this,SLOT(OnMoveJ()));
    connect(this->ui->pushButton_SpeedJ,SIGNAL(pressed()),this,SLOT(OnSpeedJ()));
    connect(this->ui->pushButton_ForceMode,SIGNAL(clicked(bool)),this,SLOT(OnForceMode()));
    connect(this->ui->pushButton_Servoc,SIGNAL(clicked(bool)),this,SLOT(onServoc()));
    connect(this->ui->pushButton_Home,SIGNAL(clicked(bool)),this,SLOT(onHome()));
    connect(this->ui->checkBox_moveJ,SIGNAL(toggled(bool)),this,SLOT(onCheckBoxMoveJ(bool)));
    connect(this->ui->checkBox_Servoc,SIGNAL(toggled(bool)),this,SLOT(onCheckBoxServoc(bool)));

    connect(ui->actionRozpocznij, SIGNAL(triggered(bool)), this,SLOT(SaveFile()));
    connect(ui->actionPlik, SIGNAL(triggered(bool)), this,SLOT(OpenFile()));
    connect(ui->actionZakoncz, SIGNAL(triggered(bool)), this,SLOT(CloseFile()));


    ur3->ConnectToRobot();
    settings->read(ur3);

}

MainWindow::~MainWindow()
{
    settings->serialize(ur3);
    //  delete settings;
    delete log;
    delete wp;
    delete ur3;
    delete ui;
}

void MainWindow::SaveFile()
{
    ui->actionRozpocznij->setChecked(true);
    ui->actionZakoncz->setChecked(false);
    log->Open();
}

void MainWindow::OpenFile()
{
    QString SaveFileName = QFileDialog::getSaveFileName(this, tr("Open text file..."), tr(""), tr("All​ ​files​ ​(*.*)"));
    ui->actionRozpocznij->setChecked(true);
    ui->actionZakoncz->setChecked(false);
    log -> Open(SaveFileName);
}

void MainWindow::CloseFile()
{
    ui->actionRozpocznij->setChecked(false);
    ui->actionZakoncz->setChecked(true);
    log->Close();
}

void MainWindow::on_actionParameters_triggered()
{
    wp->exec();
}

void MainWindow::ConnectedToInfo(char* Ip, bool Achieved)
{
    QString ip = QString(Ip);
    if (Achieved)
    {
        this->ui->lineEdit_Connection->setText("Connected with " + ip);
    }
    else
    {
        this->ui->lineEdit_Connection->setText("Connection to IP " + ip + " failed");
    }
}

void MainWindow::OnNewTCP(QVector<double> data, char a)
{
    static int refresh_interval = 0;
    static int refresh_interval_2 = 0;
    if (a == 't')
    {
        if(wp->isVisible())
            wp->PushButtonData(data);
        //log->slot_turn(1, a, data);
    }
    if (a == 't')
    {
        // if(timerr.elapsed()!=8)
   //     qDebug()<<timerr.restart();
     //   qDebug()<<"Rozkodowana, odebrana ramka";
        refresh_interval++;
        refresh_interval %=50;

        if(refresh_interval==0)
        {
            this->ui->lineEdit_Fx->setText(QString::number(data[0]));
            this->ui->lineEdit_Fy->setText(QString::number(data[1]));
            this->ui->lineEdit_Fz->setText(QString::number(data[2]));
            this->ui->lineEdit_Tx->setText(QString::number(data[3]));
            this->ui->lineEdit_Ty->setText(QString::number(data[4]));
            this->ui->lineEdit_Tz->setText(QString::number(data[5]));
        }
    }
    if (a == 'c')
    {
        refresh_interval_2++;
        refresh_interval_2 %=50;

        if(refresh_interval_2==0)
        {
            this->ui->lineEdit_Fx->setText(QString::number(data[0]));
            this->ui->lineEdit_Fy->setText(QString::number(data[1]));
            this->ui->lineEdit_Fz->setText(QString::number(data[2]));
            this->ui->lineEdit_Tx->setText(QString::number(data[3]));
            this->ui->lineEdit_Ty->setText(QString::number(data[4]));
            this->ui->lineEdit_Tz->setText(QString::number(data[5]));
        }
    }
    log->slot_turn(1, a, data);
}

void MainWindow::showConfigWindow()
{
    settings->moduleChanged(ur3);
    SettingsWindow *ustawieniaOkno = settings->getWindow(); //pobranie wskaznika do okna ustawien
    ustawieniaOkno->exec(); //wyswietlenie modalnego okna dialogowego
}

QString MainWindow::getPole2() const
{
    return pole2;
}

void MainWindow::setPole2(const QString &value)
{
    pole2 = value;
}

int MainWindow::getPole1() const
{
    return pole1;
}

void MainWindow::setPole1(int value)
{
    pole1 = value;
}

void MainWindow::OnActionConnection()
{
    this->ur3->ConnectToRobot();
}

void MainWindow::OnActionDisconnection()
{
    this->ur3->DisconnectFromRobot();
}

void MainWindow::OnMoveJ()
{
    if(wp->getV() > 0&& wp->getA() > 0)
        this->ur3->MoveJ(QVector<double>({wp->getWx(), wp->getWy(),
                                          wp->getWz(),wp->getWrx(), wp->getWy(), wp->getWz()}), wp->getV(), wp->getA());
    else
        this->ur3->MoveJ(QVector<double>({wp->getWx(), wp->getWy(),
                                          wp->getWz(),wp->getWrx(), wp->getWy(), wp->getWz()}), 1, 1);
    //  this->ur3->Servoc(QVector<double>({qSin(0.2), 1, 1, 1, 1, 1}), 1, 1);
    // this->ur3->Servoc(QVector<double>({qSin(0.3), 1, 1, 1, 1, 1}), 1, 1);
}

void MainWindow::OnSpeedJ()
{
    this->ur3->SpeedJ(QVector<double>({0,0,0,0,.1,.1}));
    //joint speed, a, t_min
}

void MainWindow::OnForceMode()
{
    if(wp->getV() > 0&& wp->getA() > 0)
        this->ur3->ForceMode(QVector<double>({0,0,0,0,0,0}),
                             QVector<double>({1,0,1,0,0,0}),
                             QVector<double>({10,0,0,0,0,0}),
                             1,
                             QVector<double>({0.1, 0.1,0.15, 0.35, 0.35, 0.35}),
                             QVector<double>({wp->getWx(), wp->getWy(),wp->getWz(),wp->getWrx(),
                                              wp->getWy(), wp->getWz()}), wp->getV(), wp->getA());
    else

        qDebug()<<"Force Mode";
    this->ur3->ForceMode(QVector<double>({0,0,0,0,0,0}),
                         QVector<double>({1,0,1,0,0,0}),
                         QVector<double>({10,0,0,0,0,0}),
                         1,
                         QVector<double>({0.1, 0.1,0.15, 0.35, 0.35, 0.35}),
                         QVector<double>({wp->getWx(), wp->getWy(),wp->getWz(),wp->getWrx(),
                                          wp->getWy(), wp->getWz()}), 1, 1);

}

void MainWindow::onHome()
{
    this->ur3->Home();
}

void MainWindow::onServoc()
{
    if(wp->getV() > 0&& wp->getA() > 0)
        this->ur3->Servoc(QVector<double>({wp->getWx(), wp->getWy(),
                                           wp->getWz(),wp->getWrx(), wp->getWy(), wp->getWz()}), wp->getV(), wp->getA());
    else
        this->ur3->Servoc(QVector<double>({wp->getWx(), wp->getWy(),
                                           wp->getWz(),wp->getWrx(), wp->getWy(), wp->getWz()}), 1, 1);

}

void MainWindow::showSettings()
{
}

void MainWindow::onCheckBoxMoveJ(bool v)
{

    ur3->banner = v;

}

void MainWindow::onCheckBoxServoc(bool v)
{
    ur3->baner_servoc = v;
}


void MainWindow::on_actionConnection_triggered()
{

}

void MainWindow::on_pushButton_MoveJ_clicked()
{


}
