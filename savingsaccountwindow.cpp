#include "savingsaccountwindow.h"
#include "ui_savingsaccountwindow.h"
#include "fetcher.h"

SavingsAccountWindow::SavingsAccountWindow(SavingsAccount account, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SavingsAccountWindow)
    , account(account)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::Window);
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->balance->setText(QString::number(account.balance));

    connect(ui->deposit, &QAbstractButton::clicked, this, &SavingsAccountWindow::deposit);
    connect(ui->withdraw, &QAbstractButton::clicked, this, &SavingsAccountWindow::withdraw);
    connect(ui->transfer_personal, &QAbstractButton::clicked, this, &SavingsAccountWindow::transferToPersonal);
    connect(ui->transfer_savings, &QAbstractButton::clicked, this, &SavingsAccountWindow::transferToSavings);
}

SavingsAccountWindow::~SavingsAccountWindow()
{
    delete ui;
}

int SavingsAccountWindow::sanitizeAmount()
{
    int amount = ui->amount->text().toInt();
    amount = amount < 0 ? -amount : amount;
    ui->amount->setText(QString::number(amount));
    return amount;
}

void SavingsAccountWindow::updateBalance()
{
    SavingsAccount latest = Fetcher::getSavingsAccount(account.id).value();
    ui->balance->setText(QString::number(latest.balance));
}

void SavingsAccountWindow::deposit()
{
    depositFunds(account.user_id, AccountType::Savings, sanitizeAmount());
}

void SavingsAccountWindow::withdraw()
{
    withdrawFunds(account.user_id, AccountType::Savings, sanitizeAmount());
}


void SavingsAccountWindow::transferToPersonal()
{
    int receiver_id = ui->receiver_user_id->text().toInt();
    transferFunds(account.user_id, AccountType::Savings, receiver_id, AccountType::Personal, sanitizeAmount());
}

void SavingsAccountWindow::transferToSavings()
{
    int receiver_id = ui->receiver_user_id->text().toInt();
    transferFunds(account.user_id, AccountType::Savings, receiver_id, AccountType::Savings, sanitizeAmount());
}
