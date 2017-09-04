#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height()); // fix size of the login dialog
}

int loginDialog::login(std::string userName, std::string password)
{
    if (userName != "" && password != "") return 1;
    return 0;
}

loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::on_pushButton_login_clicked()
{
    int loginResult = login(ui->lineEdit_username->text().toStdString(), ui->lineEdit_password->text().toStdString());

    if (loginResult) {
        this->close();
        emit loginSuccess();
    } else {
        QMessageBox::warning(this, "login failed", "username or password is incorrect");
    }
}
