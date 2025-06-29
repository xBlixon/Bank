#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QString"
#include "bankdb.h"
#include "userwindow.h"
#include "fmt/format.h"

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
    UserWindow* w = new UserWindow(this);
    QString title = QString::fromStdString(fmt::format("Logged in as: {}", ui->username->text().toStdString()));
    w->setWindowTitle(title);
    w->show();
}
