#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"
#include "ui_logindialog.h"
#include "pagesetdeck.h"
#include "global.h"
#include "Qcard.h"
#include <QTimer>
#include <QDialog>
#include <QString>
#include <QDebug>
#include <QLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer::singleShot(100, this, SLOT(showLoginDialog()));

    Global::init();
    Page::init(ui->page_setDeck);

//    x = ui->stackedWidget->addWidget(page::initSetDeck());
//    QWidget * widget = ui->stackedWidget->currentWidget();
//    QHBoxLayout * layout = widget->findChild<QHBoxLayout*>("horizontalLayout_6");
//    QPixmap image(":/images/images/card/dagon.png");
//    QLabel *imageLabel = new QLabel();
//    imageLabel->setPixmap(image);
//    imageLabel->setMinimumHeight(100);
//    imageLabel->setMinimumWidth(100);
//    layout->addWidget(imageLabel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showLoginDialog()
{
    loginDial = new loginDialog(this);
    loginDial->show();

    connect(loginDial, SIGNAL(loginSuccess(QString)), this, SLOT(goToMenu(QString)));
}

void MainWindow::changeStackedWidget(QWidget* page)
{
    ui->stackedWidget->setCurrentWidget(page);
}

void MainWindow::goToMenu(QString username)
{
    changeStackedWidget(ui->page_menu);
    ui->label_username->setText("hi, " + username);
}

void MainWindow::on_button_login_clicked()
{
    showLoginDialog();
}

void MainWindow::cardSelected(int x)
{
    QVBoxLayout *vlayout = ui->vlayout_setDeck;

    QLabel *label = new QLabel();
    QString name = QString::fromStdString(g_cardNameMap[CARDNO(x)]);
    label->setText(name);

    vlayout->insertWidget(0, label);
}

void MainWindow::on_button_setDeck_back_clicked()
{
    changeStackedWidget(ui->page_menu);
}

void MainWindow::on_button_setDeck_save_clicked()
{
    changeStackedWidget(ui->page_menu);
}

void MainWindow::on_button_menu_deck_clicked()
{
    changeStackedWidget(ui->page_setDeck);
}
