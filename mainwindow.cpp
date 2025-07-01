#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "bankdb.h"
#include "userwindow.h"
#include "fmt/format.h"
#include "QCloseEvent"
#include "iostream"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , settings("BlixSoft", "Bank")
{
    QString dbPath = getPath();
    BankDB::setPath(dbPath);
    dbPath = dbPath == "" ? "No File" : QFileInfo(dbPath).fileName();
    this->logged_users = std::vector<User>();
    ui->setupUi(this);
    QString title = QString::fromStdString(fmt::format("Bank ({})", dbPath.toStdString()));
    this->setWindowTitle(title);
    connect(ui->loadDatabase, &QAction::triggered, this, &MainWindow::loadDatabase);
    connect(ui->loginButton, &QAbstractButton::clicked, this, &MainWindow::loginUser);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    for (QWidget *widget : QApplication::topLevelWidgets()) {
        if (widget != this && widget->isVisible()) {
            event->ignore();
            return;
        }
    }
    event->accept();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::isUserLoggedIn(User& user)
{
    return std::find(logged_users.begin(), logged_users.end(), user) != logged_users.end();
}

void MainWindow::savePath(const QString& path)
{
    settings.setValue("lastDatabasePath", path);
}

QString MainWindow::getPath()
{
    return settings.value("lastDatabasePath", QString()).toString();
}

void MainWindow::loadDatabase()
{
    QString dbPath = QFileDialog::getOpenFileName(this, "Database file");
    savePath(dbPath);
    BankDB::setPath(dbPath);
    dbPath = dbPath == "" ? "No file" : dbPath;
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
    std::cout<<user.id<<std::endl;

    if(isUserLoggedIn(user)) {
        return; // User window opened already.
    }

    logged_users.push_back(user);
    UserWindow* w = new UserWindow(user, this);

    connect(w, &UserWindow::destroyed, this, [this, user = user]{
        auto it = std::find(logged_users.begin(), logged_users.end(), user);
        logged_users.erase(it);
    });

    w->show();
}
