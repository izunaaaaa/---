#include "widget.h"
#include "ui_widget.h"
#include "ui_server.h"
#include <QPushButton>
#include <QFontComboBox>
#include "loginwidget.h"
#include "server.h"
#include <QLabel>

Widget::Widget(QWidget *parent) : QWidget(parent),
   ui(new Ui::Widget)
{
    ui->setupUi(this);
    loginWidget = new LoginWidget();
    server = new Server();
    loginWidget ->show();
    connect(loginWidget , SIGNAL(server_connected()), server ,SLOT(server_connected()));
    connect(server, SIGNAL(connected()),this,SLOT(chatstart()));
    connect(loginWidget,SIGNAL(user_list(QString)),server, SLOT(receive_user(QString)));
    connect(loginWidget, SIGNAL(user_chat(QString,QString)),this, SLOT(chat_history(QString,QString)));
    connect(this, SIGNAL(send_server(QString)),loginWidget,SLOT(send_server(QString)));
    connect(loginWidget,SIGNAL(disconnect_signal()),this,SLOT(disconnect()));
}

Widget::~Widget()
{
    delete ui;
}
void Widget::on_lineEdit_returnPressed() // 엔터키 이벤트
{
    QString str = ui->lineEdit->text();
    ui->lineEdit->clear();
    emit send_server(str);
    ui->listWidget->scrollToBottom();
}
void Widget::on_send_btn_clicked() // 보내기 버튼 이벤트
{
   on_lineEdit_returnPressed();
}
void Widget::on_clear_btn_clicked() // listwidget 초기화
{
    ui->listWidget->clear();
}
void Widget::on_exit_btn_released() // 나가기 버튼
{
   this -> close();
}
void Widget::on_fontComboBox_currentFontChanged(const QFont &f) // 폰트 변경
{
    ui->listWidget->setFont(f.family());
}
void Widget::chatstart()
{
    ui->listWidget->clear();
    this -> window()-> show();
    QString text = "서버 연결 상태 ";
    ui->label->setText(text + "on");
}

void Widget::chat_history(QString name, QString chat)
{
    ui ->listWidget -> addItem(name + " : " + chat) ;
}

void Widget::disconnect()
{
    QString text = "서버 연결 상태 ";
    ui->label->setText(text + "off");
}
