#include "server.h"
#include "ui_server.h"
#include "widget.h"



Server::Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
}

Server::~Server()
{
    delete ui;
}

void Server::on_chat_btn_clicked()
{
    emit connected();
}

void Server::on_exit_btn_clicked()
{
    qApp->quit();
}

void Server::server_connected()
{
    this->show();
}

void Server::receive_user(QString user_list)
{
   ui->user_list->addItem(user_list);
}
