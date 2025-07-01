#include "userwindow.h"
#include "ui_userwindow.h"
#include "fmt/format.h"
#include "accountwindow.h"`

UserWindow::UserWindow(User& user, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserWindow)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::Window);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->user = user;

    QString title = QString::fromStdString(fmt::format("Logged in as: {}", this->user.username));
    this->setWindowTitle(title);

    connect(ui->personalButton, &QAbstractButton::clicked, this, &UserWindow::openPersonalAccount);
}

UserWindow::~UserWindow()
{
    delete ui;
}

void UserWindow::openPersonalAccount()
{
    AccountWindow* w = new AccountWindow();
    w->show();
}
