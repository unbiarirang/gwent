#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <string>
#include <QString>

namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT
signals:
    void loginSuccess(QString);

public:
    explicit loginDialog(QWidget *parent = 0);
    int login(std::string userName, std::string password);
    ~loginDialog();

private slots:
    void on_pushButton_login_clicked();

private:
    Ui::loginDialog *ui;
};

#endif // LOGINDIALOG_H
