#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

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
    void sendValue(QString name, QString chat);
    void TcpServer();

    int connect_user = 0; // 접속 유저 수
public slots:
    void newConnection();
    void disconnected();
    void readData();
};

#endif // WIDGET_H
