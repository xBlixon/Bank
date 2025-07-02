#include "adminmenu.h"
#include "ui_adminmenu.h"
#include "bankdb.h"
#include "AccountTypes.h"

AdminMenu::AdminMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AdminMenu)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::Window);
    this->setAttribute(Qt::WA_DeleteOnClose);

    connect(ui->add_user, &QAbstractButton::clicked, this, &AdminMenu::addUser);
    connect(ui->add_account, &QAbstractButton::clicked, this, &AdminMenu::addAccount);
}

AdminMenu::~AdminMenu()
{
    delete ui;
}

void AdminMenu::addUser()
{
    auto storage = BankDB::getStorage();
    std::string username = ui->username->text().toStdString();
    std::string password = ui->password->text().toStdString();

    auto data = std::make_tuple(username, password);
    storage.insert(
        into<User>(),
        columns(&User::username, &User::password),
        values(data)
        );
}

void AdminMenu::addAccount()
{
    int user_id = ui->user_id->text().toInt();
    AccountType type =
        ui->account_type->currentText() == "Personal Account" ?
        AccountType::Personal :
        AccountType::Savings ;

    auto storage = BankDB::getStorage();

    switch (type) {
    case AccountType::Personal:
        storage.insert(
            into<PersonalAccount>(),
            columns(&PersonalAccount::user_id, &PersonalAccount::balance),
            values(std::make_tuple(user_id, 0))
            );
        break;
    case AccountType::Savings:
        storage.insert(
            into<SavingsAccount>(),
            columns(&SavingsAccount::user_id, &SavingsAccount::balance, &SavingsAccount::last_login),
            values(std::make_tuple(user_id, 0, -1))
            );
        break;
    }
}
