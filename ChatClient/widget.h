#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <loginwidget.h>
#include <server.h>
#include <QTcpServer>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT


public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_exit_btn_released();
    void on_send_btn_clicked();
    void on_lineEdit_returnPressed();
    void on_clear_btn_clicked();
    void on_fontComboBox_currentFontChanged(const QFont &f);
    void chatstart();
    void chat_history(QString name, QString chat);
    void disconnect();


private:
    Ui::Widget *ui;
    LoginWidget *loginWidget;
    Server *server;
    QString name;
signals:
    void send_server(QString);
};

#endif // WIDGET_H
