#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),settings(new Settings("settings.ini", this)),  ur3(new UR3Intermediator),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ur3 = new UR3Intermediator("192.168.146.128",30002);
    connect(this->ui->actionConnection,SIGNAL(triggered(bool)),this,SLOT(OnActionConnection()));
    connect(this->ur3, SIGNAL(newPoseTCP(QVector<double>,char)),this, SLOT(OnNewTCP(QVector<double>,char)));
    connect(this->ur3,SIGNAL(ConnectionAction(char*,bool)),this,SLOT(ConnectedToInfo(char*,bool)));
    connect(ui->actionUstawienia_okna,SIGNAL(triggered(bool)),this,SLOT(showConfigWindow()));
    //connect(this->ur3, SIGNAL(newPoseTCP(QVector<double>,char)),this, SLOT(OnNewTCP(QVector<double>,char)));//
    //  connect(this->ur3, SIGNAL(newPoseTCP(QVector<double>)),this, SLOT(OnNewTCP(QVector<double>)));
    ur3->ConnectToRobot();
    settings->read(ur3);

}

MainWindow::~MainWindow()
{
    settings->serialize(ur3);//
    delete settings;//
    delete ui;
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
    //this->ui->lineEditX->setText(QString::number(data[0]));
    // this->ui->lineEditY->setText(QString::number(data[1]));
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

    this->ur3->MoveJ(QVector<double>(
    {0.6236825723301582, 1.4, 1.05, -2.5575642827418985, -1.5571205043625342, 2.781621040141847}));
    /*{0.6236825723301582, -1.477339167481995,
     2.478097719134525, -2.5575642827418985, -1.5571205043625342, 2.781621040141847}));*/
    //(q, a=1.4, v=1.05, t=0, r=0)
}

void MainWindow::OnSpeedJ()
{
    this->ur3->SpeedJ(QVector<double>({0,0,0,0,.1,.1}));
}


void MainWindow::on_actionConnection_triggered()
{
    qDebug()<<"triggered";
}

void MainWindow::on_pushButton_MoveJ_clicked()
{

}
