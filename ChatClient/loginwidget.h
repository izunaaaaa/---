#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QTcpSocket>


namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT


public:

    QTcpSocket *client;

    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();


private slots:
    void on_join_btn_clicked();
    void on_exit_btn_clicked();
    void connected();
    void receive_user();
    void send_server(QString chat);
    void disconnect();


private:
    Ui::LoginWidget *ui;
    QString user_ip;
    QString user_name;
    QString user_port;
    QString server_data;
    QString connected_user_info;
    QString chat;



signals:
    void server_connected();
    void user_list(QString);
    void user_chat(QString, QString);
    void disconnect_signal();



};

#endif // LOGINWIDGET_H00000000000
