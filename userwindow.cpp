#include "userwindow.h"
#include "ui_userwindow.h"
#include "fmt/format.h"
#include "personalaccountwindow.h"
#include "savingsaccountwindow.h"
#include "fetcher.h"

UserWindow::UserWindow(User& user, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserWindow)
    , user(user)
{
    fetchAccounts();
    ui->setupUi(this);
    this->setWindowFlag(Qt::Window);
    this->setAttribute(Qt::WA_DeleteOnClose);

    QString title = QString::fromStdString(fmt::format("Logged in as: {}", this->user.username));
    this->setWindowTitle(title);

    if(personal_account) {
        connect(ui->personalButton, &QAbstractButton::clicked, this, &UserWindow::openPersonalAccount);
    }

    if(savings_account) {
        connect(ui->savingsButton, &QAbstractButton::clicked, this, &UserWindow::openSavingsAccount);
    }
}

UserWindow::~UserWindow()
{
    delete ui;
}

void UserWindow::fetchAccounts()
{
    personal_account = Fetcher::getPersonalAccountFromUserId(user.id);
    savings_account  = Fetcher::getSavingsAccountFromUserId(user.id);
}

void UserWindow::openPersonalAccount()
{
    PersonalAccountWindow* w = new PersonalAccountWindow(personal_account.value(), this);
    w->show();
}

void UserWindow::openSavingsAccount()
{
    SavingsAccountWindow* w = new SavingsAccountWindow(savings_account.value(), this);
    w->show();
}
