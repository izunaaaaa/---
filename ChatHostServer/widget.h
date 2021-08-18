#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include "processthreadsapi.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QTcpServer *tcpserver;
    QTcpSocket *client;
    void TcpServer();
    QString user_name;
    QString user_ip;
    QString user_send_data;
    QString server_send_data;
    QString chat;
    QString user;
    int count;
    QList<QTcpSocket*> connect_user;
    QList<QString> connect_name;
public slots:
    void newConnection();
    void disconnected();
    void readInfo();


private slots:
    void on_pushButton_clicked();
    void on_lineEdit_returnPressed();

};

#endif // WIDGET_H
