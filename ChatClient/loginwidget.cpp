#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "ui_server.h"
#include <QValidator>
#include <QTcpSocket>
#include <QMessageBox>
#include <server.h>
#include <QAbstractSocket>


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
        connect(client,SIGNAL(readyRead()),this,SLOT(receive_user()));
        connect(client,SIGNAL(disconnected()),this,SLOT(disconnect()));
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
    const QString user_name = ui->lineEdit_2->text();
    QString user_ip = ui->lineEdit -> text();
    emit server_connected();
    this->hide();
    client->write("user" + user_name.trimmed().toUtf8());
}

void LoginWidget::receive_user()
{
   server_data = client->readLine().trimmed();
   qDebug() << server_data;
    if (server_data.left(4) == "user")
    {
      user_name = server_data.remove(0,4);
      emit user_list(connected_user_info);
    }
    if (server_data.left(4) == "chat")
    {
        chat = server_data.remove(0,4);
        QStringList list = chat.split(":");
        user_name = list[0];
        chat = list[1];
        emit user_chat(user_name, chat);
    }
    if (server_data.left(6) == "server")
    {
        chat = server_data.remove(0,6);
        QString user_name = "server";
        emit user_chat(user_name, chat);
    }
}

void LoginWidget::send_server(QString chat)
{
    client->write("chat" + chat.trimmed().toUtf8());
}

void LoginWidget::disconnect()
{
    emit disconnect_signal();
}
