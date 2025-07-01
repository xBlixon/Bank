#include "accountwindowbase.h"
#include "fetcher.h"
#include "personalaccount.h"

AccountWindowBase::AccountWindowBase() {}

void AccountWindowBase::depositFunds(int user_id, AccountType type, int amount)
{
    amount = amount < 0 ? -amount : amount;
    auto storage = BankDB::getStorage();
    switch (type) {
    case AccountType::Personal: {
        storage.update_all(
            set(c(&PersonalAccount::balance) = c(&PersonalAccount::balance) + amount),
            where(c(&PersonalAccount::user_id) == user_id)
            );
        break;
    }
    case AccountType::Savings:
        break;
    }

    updateBalance();
}

void AccountWindowBase::withdrawFunds(int user_id, AccountType type, int amount)
{
    auto storage = BankDB::getStorage();
    switch (type) {
    case AccountType::Personal: {
        PersonalAccount a = Fetcher::getPersonalAccountFromUserId(user_id);
        amount = amount < 0 ? -amount : amount;
        int newAmount = a.balance - amount;
        newAmount = newAmount < 0 ? 0 : newAmount;
        storage.update_all(
            set(c(&PersonalAccount::balance) = newAmount),
            where(c(&PersonalAccount::user_id) == user_id)
            );
        break;
    }
    case AccountType::Savings:
        break;
    }

    updateBalance();

}

