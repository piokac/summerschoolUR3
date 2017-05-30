#include "controlpanel.h"
#include "ui_controlpanel.h"

controlpanel::controlpanel(QWidget *parent) :
    QWidget(parent),p_checkbox(NULL),
    ui(new Ui::controlpanel)
{

    ui->setupUi(this);


    //setting icons

    ui->turnRightButton->setIcon(QIcon(":/resources/img/Button-Previous-icon.png"));
     ui->turnRightButton->setIconSize(QSize(65,65));
     ui->turnRightButton->setStyleSheet("background-color:transparent");
     ui->turnLeftButton->setIcon(QIcon(":/resources/img/Button-Next-icon.png"));
      ui->turnLeftButton->setIconSize(QSize(65,65));
      ui->turnLeftButton->setStyleSheet("background-color:transparent");
      ui->turnManipulatorLeft->setIcon(QIcon(":/resources/img/Button-Reload-icon (1).png"));
      ui->turnManipulatorLeft->setIconSize(QSize(75,75));
      ui->turnManipulatorLeft->setStyleSheet("background-color:transparent");
      ui->turnManipulatorRight->setIcon(QIcon(":/resources/img/Button-Reload-icon.png"));
      ui->turnManipulatorRight->setIconSize(QSize(75,75));
      ui->turnManipulatorRight->setStyleSheet("background-color:transparent");
      ui->manipulatorUpButton->setIcon(QIcon(":/resources/img/sign-up-icon.png"));
      ui->manipulatorUpButton->setIconSize(QSize(75,75));
      ui->manipulatorUpButton->setStyleSheet("background-color:transparent");
      ui->manipulatorDownButton->setIcon(QIcon(":/resources/img/sign-down-icon.png"));
      ui->manipulatorDownButton->setIconSize(QSize(75,75));
      ui->manipulatorDownButton->setStyleSheet("background-color:transparent");
      ui->manipulatorLeftButton->setIcon(QIcon(":/resources/img/sign-left-icon.png"));
      ui->manipulatorLeftButton->setIconSize(QSize(75,75));
      ui->manipulatorLeftButton->setStyleSheet("background-color:transparent");
      ui->manipulatorRightButton->setIcon(QIcon(":/resources/img/sign-right-icon.png"));
      ui->manipulatorRightButton->setIconSize(QSize(75,75));
      ui->manipulatorRightButton->setStyleSheet("background-color:transparent");

      //settings window

      QMenuBar* menu=new QMenuBar(this);
        QMenu* settings= menu->addMenu("Control Panel");
       QAction* setSet=settings->addAction(QIcon(":/resources/img/1496162808_settings.png"),"Settings");
        connect(setSet,SIGNAL(triggered(bool)),this,SLOT(showSettings()));


        //setting states
    /*   if(joint1isgood)
        {
       */  setBoxNot(ui->joint1Pixmap);
         /*
         }
        else
        setBoxNot(ui->joint1Pixmap);


        if(joint2isgood)
        {
            setBoxOK((ui->joint2Pixmap));
        }
        else
        setBoxNot((ui->joint2Pixmap));


        if(joint3isgood)
        {
            setBoxOK((ui->joint3Pixmap);
        }
        else
        setBoxNot((ui->joint3Pixmap));


        if(baseisok)
        {
            setBoxOK((ui->basePixmap));
        }
        else
        setBoxNot(ui->basePixmap);

        if(shoulderisok)
        {
            setBoxOK(ui->shoulderPixmap);
        }
        else
        setBoxNot(ui->shoulderPixmap);


        if(elbowisok)
        {
            setBoxOK((ui->elbowPixmap));
        }
        else
        setBoxNot(ui->elbowPixmap);
        */

}
// get Settings to DataGroupBox

void controlpanel::getSettings(Dialog *settingsDialog)
{
    ui->groupBox->setLayout(ui->groupVerticalLay);
       if(p_checkbox!=NULL)
       {
           p_checkbox->deleteLater();
       }
       p_checkbox=new QWidget(this);

       if(settingsDialog->giveCurrentdc())
       {

          QLabel* currentdc=new QLabel(p_checkbox);
          currentdc->setText("Current dc");
          QTextEdit* currentdCText=new QTextEdit(p_checkbox);
          //currentdCText->setText(dane z robota);
          QHBoxLayout* layoutdc=new QHBoxLayout(p_checkbox);
          layoutdc->addWidget(currentdc);
          layoutdc->addWidget(currentdCText);
          QVBoxLayout* layoutofCurrent=new QVBoxLayout(p_checkbox);
          layoutofCurrent->addLayout(layoutdc);
          ui->groupVerticalLay->addLayout(layoutofCurrent);

       }
       if(settingsDialog->givePower())
       {

          QLabel* power=new QLabel(p_checkbox);
          power->setText("Power: ");
          QTextEdit* powerText=new QTextEdit(p_checkbox);
          //powerText->setText(dane z robota);
          QHBoxLayout* layoutpower=new QHBoxLayout(p_checkbox);
          layoutpower->addWidget(power);
          layoutpower->addWidget(powerText);
          QVBoxLayout* layoutofPower=new QVBoxLayout(p_checkbox);
          layoutofPower->addLayout(layoutpower);
          ui->groupVerticalLay->addLayout(layoutofPower);

       }

       if(settingsDialog->giveTemperature())
       {

          QLabel* temperature=new QLabel(p_checkbox);
          temperature->setText("Temperature: ");
          QTextEdit* temperatureText=new QTextEdit(p_checkbox);
          //temperatureText->setText(dane z robota);
          QHBoxLayout* layoutemperature=new QHBoxLayout(p_checkbox);
          layoutemperature->addWidget(temperature);
          layoutemperature->addWidget(temperatureText);
          QVBoxLayout* layoutofTemperature=new QVBoxLayout(p_checkbox);
          layoutofTemperature->addLayout(layoutemperature);
          ui->groupVerticalLay->addLayout(layoutofTemperature);

       }

       if(settingsDialog->giveVoltage())
       {

          QLabel* voltage=new QLabel(p_checkbox);
          voltage->setText("Voltage: ");
          QTextEdit* voltageText=new QTextEdit(p_checkbox);
          //voltageText->setText(dane z robota);
          QHBoxLayout* layoutvoltage=new QHBoxLayout(p_checkbox);
          layoutvoltage->addWidget(voltage);
          layoutvoltage->addWidget(voltageText);
          QVBoxLayout* layoutofVoltage=new QVBoxLayout(p_checkbox);
          layoutofVoltage->addLayout(layoutvoltage);
          ui->groupVerticalLay->addLayout(layoutofVoltage);

       }
       if(settingsDialog->giveX())
       {

          QLabel* X=new QLabel(p_checkbox);
          X->setText("X");
          QTextEdit* XText=new QTextEdit(p_checkbox);
          //XText->setText(dane z robota);
          QHBoxLayout* layoutX=new QHBoxLayout(p_checkbox);
          layoutX->addWidget(X);
          layoutX->addWidget(XText);
          QVBoxLayout* layoutofX=new QVBoxLayout(p_checkbox);
          layoutofX->addLayout(layoutX);
          ui->groupVerticalLay->addLayout(layoutofX);

       }
       if(settingsDialog->giveY())
       {

          QLabel* Y=new QLabel(p_checkbox);
          Y->setText("Y");
          QTextEdit* YText=new QTextEdit(p_checkbox);
          //YText->setText(dane z robota);
          QHBoxLayout* layoutY=new QHBoxLayout(p_checkbox);
          layoutY->addWidget(Y);
          layoutY->addWidget(YText);
          QVBoxLayout* layoutofY=new QVBoxLayout(p_checkbox);
          layoutofY->addLayout(layoutY);
          ui->groupVerticalLay->addLayout(layoutofY);

       }
       if(settingsDialog->giveZ())
       {

          QLabel* Z=new QLabel(p_checkbox);
          Z->setText("Z");
          QTextEdit* ZText=new QTextEdit(p_checkbox);
          //ZText->setText(dane z robota);
          QHBoxLayout* layoutZ=new QHBoxLayout(p_checkbox);
          layoutZ->addWidget(Z);
          layoutZ->addWidget(ZText);
          QVBoxLayout* layoutofZ=new QVBoxLayout(p_checkbox);
          layoutofZ->addLayout(layoutZ);

          ui->groupVerticalLay->addLayout(layoutofZ);
       }






}

void controlpanel::setBoxOK(QLabel *label)
{
   QPixmap pix(":/resources/img/Button-Ok-icon.png");
 QPixmap PixmapForLabel=pix.scaled(QSize(30,30),Qt::KeepAspectRatio,Qt::FastTransformation);
   label->setPixmap(PixmapForLabel);
   label->setStyleSheet("background-color:transparent");
}

void controlpanel::setBoxNot(QLabel *label)
{
    QPixmap pix(":/resources/img/Button-Delete-icon.png");
    QPixmap PixmapForLabel=pix.scaled(QSize(30,30),Qt::KeepAspectRatio,Qt::FastTransformation);
      label->setPixmap(PixmapForLabel);
      label->setStyleSheet("background-color:transparent");
}

void controlpanel::showSettings()
{   Dialog settDialog;
    if(settDialog.exec()==QDialog::Accepted)
    {
     //cleaning grouboxlayout
    }
    if(settDialog.close()==QDialog::Accepted)
    {
        getSettings(&settDialog);
    }
}


controlpanel::~controlpanel()
{
    delete ui;
}
