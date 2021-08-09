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


private:
    Ui::LoginWidget *ui;
    QString user_ip;
    QString user_name;
    QString user_port;



signals:
    void server_connected(QString);



};

#endif // LOGINWIDGET_H00000000000
