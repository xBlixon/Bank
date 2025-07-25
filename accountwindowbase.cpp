#include "accountwindowbase.h"
#include "fetcher.h"
#include "personalaccount.h"

AccountWindowBase::AccountWindowBase() {}

void AccountWindowBase::depositFunds(int user_id, AccountType type, int amount)
{
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
        storage.update_all(
            set(c(&SavingsAccount::balance) = c(&SavingsAccount::balance) + amount),
            where(c(&SavingsAccount::user_id) == user_id)
            );
        break;
    }

    updateBalance();
}

void AccountWindowBase::withdrawFunds(int user_id, AccountType type, int amount)
{
    auto storage = BankDB::getStorage();
    switch (type) {
    case AccountType::Personal: {
        PersonalAccount a = Fetcher::getPersonalAccountFromUserId(user_id).value();
        int newAmount = a.balance - amount;
        newAmount = newAmount < 0 ? 0 : newAmount; //Clamping from 0 to +
        storage.update_all(
            set(c(&PersonalAccount::balance) = newAmount),
            where(c(&PersonalAccount::user_id) == user_id)
            );
        break;
    }
    case AccountType::Savings:
        SavingsAccount a = Fetcher::getSavingsAccountFromUserId(user_id).value();
        int newAmount = a.balance - amount;
        newAmount = newAmount < 0 ? 0 : newAmount; //Clamping from 0 to +
        storage.update_all(
            set(c(&SavingsAccount::balance) = newAmount),
            where(c(&SavingsAccount::user_id) == user_id)
            );
        break;
    }

    updateBalance();

}

void AccountWindowBase::transferFunds(int sender_id, AccountType sender_type, int receiver_id, AccountType receiver_type, int amount)
{
    int balance = -1;
    switch (sender_type) {
    case AccountType::Personal: {
        balance = Fetcher::getPersonalAccountFromUserId(sender_id).value().balance;
        break;
    }
    case AccountType::Savings:
        balance = Fetcher::getSavingsAccountFromUserId(sender_id).value().balance;
        break;
    }

    if(balance - amount < 0) {
        return; // User can't afford.
    }
    auto storage = BankDB::getStorage();

    switch (receiver_type) {
    case AccountType::Personal: {
        std::optional<PersonalAccount> receiver = Fetcher::getPersonalAccountFromUserId(receiver_id);
        if(!receiver.has_value()) {
            return; //Check if account exists before proceeding.
        }
        storage.update_all(
            set(c(&PersonalAccount::balance) = c(&PersonalAccount::balance) + amount),
            where(c(&PersonalAccount::user_id) == receiver_id)
            );
        break;
    }
    case AccountType::Savings:
        std::optional<SavingsAccount> receiver = Fetcher::getSavingsAccountFromUserId(receiver_id);
        if(!receiver.has_value()) {
            return; //Check if account exists before proceeding.
        }
        storage.update_all(
            set(c(&SavingsAccount::balance) = c(&SavingsAccount::balance) + amount),
            where(c(&SavingsAccount::user_id) == receiver_id)
            );
        break;
    }

    switch (sender_type) {
    case AccountType::Personal:
        storage.update_all(
            set(c(&PersonalAccount::balance) = c(&PersonalAccount::balance) - amount),
            where(c(&PersonalAccount::user_id) == sender_id)
            );
        break;
    case AccountType::Savings:
        storage.update_all(
            set(c(&SavingsAccount::balance) = c(&SavingsAccount::balance) - amount),
            where(c(&SavingsAccount::user_id) == sender_id)
            );
        break;
    }

    updateBalance();
}

