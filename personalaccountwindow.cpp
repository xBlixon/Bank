#include "personalaccountwindow.h"
#include "ui_personalaccountwindow.h"
#include "fetcher.h"

PersonalAccountWindow::PersonalAccountWindow(PersonalAccount account, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PersonalAccountWindow)
    , account(account)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::Window);
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->balance->setText(QString::number(account.balance));

    connect(ui->deposit, &QAbstractButton::clicked, this, &PersonalAccountWindow::deposit);
    connect(ui->withdraw, &QAbstractButton::clicked, this, &PersonalAccountWindow::withdraw);
}

PersonalAccountWindow::~PersonalAccountWindow()
{
    delete ui;
}

void PersonalAccountWindow::updateBalance()
{
    PersonalAccount latest = Fetcher::getPersonalAccount(account.id);
    ui->balance->setText(QString::number(latest.balance));
}

void PersonalAccountWindow::deposit()
{
    int amount = ui->amount->text().toInt();
    depositFunds(account.user_id, AccountType::Personal, amount);
}

void PersonalAccountWindow::withdraw()
{
    int amount = ui->amount->text().toInt();
    withdrawFunds(account.user_id, AccountType::Personal, amount);
}
