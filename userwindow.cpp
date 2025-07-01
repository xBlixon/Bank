#include "userwindow.h"
#include "ui_userwindow.h"
#include "fmt/format.h"
#include "bankdb.h"

UserWindow::UserWindow(User& user, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserWindow)
{
    fetchAccounts();
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

void UserWindow::fetchAccounts()
{
    auto storage = BankDB::getStorage();

    std::vector<PersonalAccount> personals = storage.get_all<PersonalAccount>(
        where(c(&PersonalAccount::user_id) == user.id),
        limit(1)
        );
    if(!personals.empty()) {
        personal_account = personals.at(0);
    }
}

void UserWindow::openPersonalAccount()
{
}
