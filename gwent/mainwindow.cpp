#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"
#include "ui_logindialog.h"
#include <QTimer>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    stackedWidget(new QStackedWidget)
{
    ui->setupUi(this);

    QTimer::singleShot(100, this, SLOT(showLoginDialog()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showLoginDialog()
{
    loginDial = new loginDialog(this);
    loginDial->show();

    connect(loginDial, SIGNAL(loginSuccess()), this, SLOT(changeStackedWidget()));
}

void MainWindow::changeStackedWidget()
{
    stackedWidget = ui->stackedWidget;
    stackedWidget->setCurrentIndex(1);
}

