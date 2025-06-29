#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "bankdb.h"
#include "userwindow.h"
#include "fmt/format.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Bank (No file)");
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
    std::string fileName = QFileInfo(dbPath).fileName().toStdString();
    QString title = QString::fromStdString(fmt::format("Bank ({})", fileName));
    this->setWindowTitle(title);
}

void MainWindow::loginUser()
{
    auto storage = BankDB::getStorage();
    std::string username = ui->username->text().toStdString();
    std::string password = ui->password->text().toStdString();

    auto rows = storage.get_all<User>(
                               where((c(&User::username) == username) and (c(&User::password) == password)),
                               limit(1)
        );

    if(rows.empty()) {
        return; //No such user - don't do anything.
    }
    User user = rows.at(0);
    UserWindow* w = new UserWindow(user, this);
    w->show();
}
