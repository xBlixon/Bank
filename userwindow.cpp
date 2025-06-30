#include "userwindow.h"
#include "ui_userwindow.h"
#include "fmt/format.h"

UserWindow::UserWindow(User& user, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserWindow)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::Window);
    this->user = user;

    QString title = QString::fromStdString(fmt::format("Logged in as: {}", this->user.username));
    this->setWindowTitle(title);
}

UserWindow::~UserWindow()
{
    delete ui;
}
