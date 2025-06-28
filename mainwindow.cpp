#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QFileDialog"
#include "QString"
#include "bankdb.h"
#include "userwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->loadDatabase, &QAction::triggered, this, &MainWindow::loadDatabase);
    connect(ui->loginButton, &QAbstractButton::clicked, this, &MainWindow::loginUser);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadDatabase()
{
    QString dbPath = QFileDialog::getOpenFileName(this, "Database file");
    BankDB::setPath(dbPath.toStdString());
}

void MainWindow::loginUser()
{
    ui->username->setText("Activated");
    UserWindow w(this);
    w.setWindowTitle("User Menu");
    w.show();
}
