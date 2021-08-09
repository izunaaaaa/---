#include "loginwidget.h"
#include "ui_loginwidget.h"
#include <QValidator>
#include <QTcpSocket>
#include <QMessageBox>
#include <server.h>


LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";

        QRegExp ipRegex ("^" + ipRange
                             + "." + ipRange
                             + "." + ipRange
                             + "." + ipRange + "$");

        QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
        ui->lineEdit->setValidator(ipValidator);
        client = new QTcpSocket();
        connect(client,SIGNAL(connected()),this,SLOT(connected()));
}

LoginWidget::~LoginWidget()
{
    delete ui;
}
void LoginWidget::on_join_btn_clicked()
{    
        QHostAddress hostaddress;
        QString user_name = ui->lineEdit_2->text();
        QString user_port = ui ->lineEdit_3->text();
        QString user_ip = ui->lineEdit -> text();
        qDebug() << hostaddress.LocalHost;
            if (user_port=="0416"){
                    quint16 user_port = 0416;
                    if (user_name !=""){
                            client->connectToHost(user_ip,user_port);
                               qDebug() <<  "try to connect..";
                                       }
                    else {
                          QMessageBox::critical(this,"오류","이름 입력");
                          qDebug() << user_name;
                         }
             }
             else {
                 QMessageBox::critical(this,"오류","포트 번호 0416");
                 qDebug()<<user_port;
             }
}


void LoginWidget::on_exit_btn_clicked()
{
    this -> close();
}

void LoginWidget::connected()
{
    qDebug() << "success connect";
    QString user_name = ui->lineEdit_2->text();
    QString user_ip = ui->lineEdit -> text();
    emit server_connected(user_name,user_ip);
    this->hide();
}

