#include "widget.h"
#include "server.h"
#include "loginwidget.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("chat");
    w.hide();



    return a.exec();

}
