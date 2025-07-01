#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "bankdb.h"
#include "userwindow.h"
#include "fmt/format.h"
#include "QCloseEvent"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->logged_users = std::vector<User>();
    ui->setupUi(this);
    this->setWindowTitle("Bank (No file)");
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
