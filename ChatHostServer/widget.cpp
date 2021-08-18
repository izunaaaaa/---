#include "widget.h"
#include "ui_widget.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QAbstractSocket>
#include <QPushButton>



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    tcpserver = new QTcpServer(this);
    TcpServer();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::TcpServer()
{
    QHostAddress hostAddress;
    count = 0;
    if(!tcpserver->listen(QHostAddress::Any, 0416))
        {
            // 서버가 가동이 되지 않으면 메시지 출력
            qDebug()<<"Server could not start!"; // qDebug 1
        }
        else
        {
            // 서버가 가동 중이면 start 메시지 출력
            qDebug()<< "Server started" <<"user count :" <<connect_user;
        }
    connect(tcpserver, SIGNAL(newConnection()),this, SLOT(newConnection()));
}

void Widget::newConnection()
{
   while(tcpserver->hasPendingConnections())
   {
    QTcpSocket *client = tcpserver->nextPendingConnection();  
    connect(client, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(client,SIGNAL(readyRead()),this,SLOT(readInfo()));
    connect_user.append(client);
   }
}

void Widget::disconnected()
{
    QTcpSocket *client = static_cast<QTcpSocket*>(sender());
    qDebug() << "disconnet user " << user_send_data << " user count :" << connect_user;
    client->deleteLater();
}

void Widget::readInfo()
{
    QTcpSocket *client = static_cast<QTcpSocket*>(sender());
    user_send_data = client->readLine().trimmed();
    if (user_send_data.left(4) == "user")
    {
        user = user_send_data;
        connect_name.append(user);
        foreach(client,connect_user)
        {
            foreach(user,connect_name)
            {
                 client->write(user.toUtf8());
            }
        }
        count++;
        ui->user_count->setText("접속 유저수 : " + QString::number(count));
        ui->user_list->addItem(user.remove(0,4) + client->peerAddress().toString());
        user = connect_name.last();
        qDebug() << user;
    }

    if (user_send_data.left(4) == "chat"){
        chat = user_send_data;
        foreach(client,connect_user)
        {
        client->write(user.toUtf8() +":"+ chat.toUtf8());
        }
        ui->user_chat->addItem(user +" : "+chat);
    }
    ui->user_chat->scrollToBottom();
}

void Widget::on_pushButton_clicked()
{
    server_send_data = ui->lineEdit->text();
    ui->user_chat->addItem("server: " + server_send_data);
    ui->user_chat->scrollToBottom();
    server_send_data = "server" + ui->lineEdit->text();
    ui->lineEdit->clear();
    foreach(client,connect_user)    // connect_user에 수집된 유저정보로 보내기
    {
    client->write(server_send_data.toUtf8());
    }
}

void Widget::on_lineEdit_returnPressed()
{
    on_pushButton_clicked();
}
