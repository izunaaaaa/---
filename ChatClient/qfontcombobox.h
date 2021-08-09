#ifndef QFONTCOMBOBOX_H
#define QFONTCOMBOBOX_H

#include <QComboBox>
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void fontChanged();


private:
    QComboBox *combo;
};
#endif // QFONTCOMBOBOX_H
