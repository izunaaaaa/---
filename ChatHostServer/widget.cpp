#include "widget.h"
#include "ui_widget.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QAbstractSocket>



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setMinimumSize(200,100);
    setMaximumSize(200,100);
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
    if(!tcpserver->listen(QHostAddress::Any, 0416))
        {
            // 서버가 가동이 되지 않으면 메시지 출력
            qDebug()<<"Server could not start!";
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
    connect_user += 1;
    qDebug() << "Connect" << "접속 유저 수 : " << connect_user;
    connect(client, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(client,SIGNAL(readRead()),this,SLOT(readData()));
   }
}

void Widget::disconnected()
{
    connect_user -= 1;
    qDebug() << "disconnet user" << "접속 유저 수 :" << connect_user;
}

void Widget::readData()
{
    qDebug() << " 구현중 " ;
}
