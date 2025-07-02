#include "savingsaccountwindow.h"
#include "ui_savingsaccountwindow.h"
#include "fetcher.h"
#include "ctime"

SavingsAccountWindow::SavingsAccountWindow(SavingsAccount account, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SavingsAccountWindow)
    , account(account)
{
    giveInterest();
    ui->setupUi(this);
    this->setWindowFlag(Qt::Window);
    this->setAttribute(Qt::WA_DeleteOnClose);
    updateBalance();

    connect(ui->deposit, &QAbstractButton::clicked, this, &SavingsAccountWindow::deposit);
    connect(ui->withdraw, &QAbstractButton::clicked, this, &SavingsAccountWindow::withdraw);
    connect(ui->transfer_personal, &QAbstractButton::clicked, this, &SavingsAccountWindow::transferToPersonal);
    connect(ui->transfer_savings, &QAbstractButton::clicked, this, &SavingsAccountWindow::transferToSavings);
}

SavingsAccountWindow::~SavingsAccountWindow()
{
    delete ui;
}

void SavingsAccountWindow::giveInterest()
{
    int loginTime = std::time(nullptr);

    auto storage = BankDB::getStorage();
    if(account.last_login == -1) {
        storage.update_all(
        set(
            c(&SavingsAccount::last_login) = loginTime
            ),
        where(c(&SavingsAccount::id) = account.id)
        );
        return; // Never logged in before
    }

    int timeDifference = loginTime - account.last_login;
    int interest = timeDifference/5;

    storage.update_all(
        set(
            c(&SavingsAccount::last_login) = loginTime,
            c(&SavingsAccount::balance) = c(&SavingsAccount::balance) + interest
            ),
        where(c(&SavingsAccount::id) = account.id)
        );
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
