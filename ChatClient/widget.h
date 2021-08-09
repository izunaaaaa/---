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
    void count_user();


private:
    Ui::Widget *ui;
    LoginWidget *loginWidget;
    Server *server;
    QString name;
};

#endif // WIDGET_H
