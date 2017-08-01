#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"planecallibration.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),settings(new Settings("settings.ini", this)),  ur3(new UR3Intermediator), wp(new WayPoint),
    ui(new Ui::MainWindow)
{
    pl = new PlaneCallibration(ur3,this);

    ui->setupUi(this);
    connect(this->ui->actionConnection,SIGNAL(triggered(bool)),this,SLOT(OnActionConnection()));
    connect(this->ur3, SIGNAL(newPoseTCP(QVector<double>,char)),this, SLOT(OnNewTCP(QVector<double>,char)));
    connect(this->ur3,SIGNAL(ConnectionAction(char*,bool)),this,SLOT(ConnectedToInfo(char*,bool)));
    connect(ui->actionUstawienia_okna,SIGNAL(triggered(bool)),this,SLOT(showConfigWindow()));
    connect(this->ui->pushButton_MoveJ,SIGNAL(clicked(bool)),this,SLOT(OnMoveJ()));
    connect(this->ui->pushButton_SpeedJ,SIGNAL(pressed()),this,SLOT(OnSpeedJ()));
    connect(this->ui->pushButton_ForceMode,SIGNAL(clicked(bool)),this,SLOT(OnForceMode()));
    connect(this->ui->pushButton_Servoc,SIGNAL(clicked(bool)),this,SLOT(onServoc()));
    connect(this->ui->pushButton_Home,SIGNAL(clicked(bool)),this,SLOT(onHome()));

   // connect(this->ui->actionParameters,SIGNAL(clicked(bool)),this,SLOT(showWayPoint()));
    //connect(ui->actionParameters,SIGNAL(triggered(bool)),this,SLOT(showWayPoint()));
      connect(this->ui->actionParameters, SIGNAL(triggered(bool)), this, SLOT(showWayPoint()));
      connect(this->ui->actionPlane_Callibration, SIGNAL(triggered(bool)),this,SLOT(showPlaneCallibration()));
   // connect(this->ui->actionPlane_Callibration, SIGNAL(triggered(bool)), this, SLOT(()));


    ur3->ConnectToRobot();
    settings->read(ur3);

}

MainWindow::~MainWindow()
{
    settings->serialize(ur3);//
    delete settings;//
    delete ui;
}

void MainWindow::on_actionParameters_triggered()
{
   // WayPoint * wp;
    if(wp->exec() == QDialog::Accepted)
    {               
       /* wp->setWx(1);
        double  a =  wp->getWx();*/
        wp->getWx();
        wp->getWy();
        wp->getWz();
        wp->getWrx();
        wp->getWry();
        wp->getWrz();
        wp->getV();
        wp->getA();

        //qDebug()<<a<<"yjfyjf "<<wp->getWx();
    }
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

    if(a=='t')
    {       
        wp->PushButtonData(data);
    }

    if (a == 'f')
    {
        this->ui->lineEdit_Fx->setText(QString::number(data[0]));
        this->ui->lineEdit_Fy->setText(QString::number(data[1]));
        this->ui->lineEdit_Fz->setText(QString::number(data[2]));
        this->ui->lineEdit_Tx->setText(QString::number(data[3]));
        this->ui->lineEdit_Ty->setText(QString::number(data[4]));
        this->ui->lineEdit_Tz->setText(QString::number(data[5]));
    }
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

void MainWindow::OnMoveJ()
{

 /*   this->ur3->MoveJ(QVector<double>(
                         // {0.6236825723301582, 1.4, 1.05, -2.5575642827418985, -1.5571205043625342, 2.781621040141847}));
    {0.6236825723301582, -1.477339167481995,
     2.478097719134525, -2.5575642827418985, -1.5571205043625342, 2.781621040141847}), 2.4, 3);
    //(q, a=1.4, v=1.05, t=0, r=0)*/
  //  double a = wp->getWx();
    this->ur3->MoveJ(QVector<double>({wp->getWx(), wp->getWy(),
       wp->getWz(),wp->getWrx(), wp->getWy(), wp->getWz()}), wp->getV(), wp->getA());
    qDebug()<<wp->getWx();



}

void MainWindow::OnSpeedJ()
{
    this->ur3->SpeedJ(QVector<double>({0,0,0,0,.1,.1}));
    //joint speed, a, t_min
}

void MainWindow::OnForceMode()
{
    this->ur3->ForceMode(QVector<double>({0,0,0,0,0,0}),
                         QVector<double>({1,0,1,0,0,0}),
                         QVector<double>({10,0,0,0,0,0}),
                         1,
                         QVector<double>({0.1, 0.1,0.15, 0.35, 0.35, 0.35}));
    qDebug()<<"Force Mode";
}

void MainWindow::onHome()
{
    this->ur3->Home();
}

void MainWindow::onServoc()
{
  /*  this->ur3->Servoc(QVector<double>(
    {0.6236825723301582, -1.477339167481995,2.478097719134525, -2.5575642827418985, -1.5571205043625342, 2.781621040141847}), 1.2, 0.5);
    this->ur3->Servoc(QVector<double>(
    {-193.55,-16.44,294.15,2.255,2.454,-2.454}), 2.4, 1);
    this->ur3->Servoc(QVector<double>(
    {0.6236825723301582, -1.477339167481995,2.478097719134525, -2.5575642827418985, -1.5571205043625342, 2.781621040141847}), 1.2, 0.5);
*/
}

void MainWindow::showSettings()
{

}

void MainWindow::showWayPoint()
{
    wp->getWx();
    wp->getWy();
    wp->getWz();
    wp->getWrx();
    wp->getWry();
    wp->getWrz();
    wp->getV();
    wp->getA();
}

void MainWindow::showPlaneCallibration()
{
    pl->run_callibration();
    //PlaneCallibration planecallibration;

    /*if(planecallibration.exec() == QDialog::Accepted)
    {
        qDebug()<<"ok";
    }*/
}


void MainWindow::on_actionConnection_triggered()
{
    qDebug()<<"triggered";
}

void MainWindow::on_pushButton_MoveJ_clicked()
{
    qDebug()<<"MoveJ";

}

