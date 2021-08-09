#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>
#include <QFontComboBox>
#include "loginwidget.h"
#include "server.h"

Widget::Widget(QWidget *parent) : QWidget(parent),
   ui(new Ui::Widget)
{
    ui->setupUi(this);
    loginWidget = new LoginWidget();
    server = new Server();
    loginWidget ->show();
    connect(loginWidget , SIGNAL(server_connected(QString)), server ,SLOT(server_connected(QString)));
    connect(server, SIGNAL(connected()),this,SLOT(chatstart()));
}

Widget::~Widget()
{
    delete ui;
}
void Widget::on_lineEdit_returnPressed() // 엔터키 이벤트
{
    QString str = ui->lineEdit->text();
    ui ->listWidget -> addItem(" : " + str) ;
    ui->lineEdit->clear();
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
    this -> window()-> show();
}
