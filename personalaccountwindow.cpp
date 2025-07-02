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
    updateBalance();

    connect(ui->deposit, &QAbstractButton::clicked, this, &PersonalAccountWindow::deposit);
    connect(ui->withdraw, &QAbstractButton::clicked, this, &PersonalAccountWindow::withdraw);
    connect(ui->transfer_personal, &QAbstractButton::clicked, this, &PersonalAccountWindow::transferToPersonal);
    connect(ui->transfer_savings, &QAbstractButton::clicked, this, &PersonalAccountWindow::transferToSavings);
}

PersonalAccountWindow::~PersonalAccountWindow()
{
    delete ui;
}

int PersonalAccountWindow::sanitizeAmount()
{
    int amount = ui->amount->text().toInt();
    amount = amount < 0 ? -amount : amount;
    ui->amount->setText(QString::number(amount));
    return amount;
}

void PersonalAccountWindow::updateBalance()
{
    PersonalAccount latest = Fetcher::getPersonalAccount(account.id).value();
    ui->balance->setText(QString::number(latest.balance));
}

void PersonalAccountWindow::deposit()
{
    depositFunds(account.user_id, AccountType::Personal, sanitizeAmount());
}

void PersonalAccountWindow::withdraw()
{
    withdrawFunds(account.user_id, AccountType::Personal, sanitizeAmount());
}


void PersonalAccountWindow::transferToPersonal()
{
    int receiver_id = ui->receiver_user_id->text().toInt();
    transferFunds(account.user_id, AccountType::Personal, receiver_id, AccountType::Personal, sanitizeAmount());
}

void PersonalAccountWindow::transferToSavings()
{
    int receiver_id = ui->receiver_user_id->text().toInt();
    transferFunds(account.user_id, AccountType::Personal, receiver_id, AccountType::Savings, sanitizeAmount());

}
