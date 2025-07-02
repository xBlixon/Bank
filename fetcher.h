#ifndef FETCHER_H
#define FETCHER_H
#include "bankdb.h"

class Fetcher
{
public:
    static std::optional<PersonalAccount> getPersonalAccountFromUserId(int user_id) {
        auto storage = BankDB::getStorage();
        auto rows = storage.get_all<PersonalAccount>(
            where(c(&PersonalAccount::user_id) == user_id)
            );
        if(rows.empty()) {
            return std::optional<PersonalAccount>();
        }
        return rows.front();

    }

    static std::optional<PersonalAccount> getPersonalAccount(int id) {
        auto storage = BankDB::getStorage();
        auto rows = storage.get_all<PersonalAccount>(
            where(c(&PersonalAccount::id) == id)
            );
        if(rows.empty()) {
            return std::optional<PersonalAccount>();
        }
        return rows.front();

    }

    static std::optional<SavingsAccount> getSavingsAccountFromUserId(int user_id) {
        auto storage = BankDB::getStorage();
        auto rows = storage.get_all<SavingsAccount>(
            where(c(&SavingsAccount::user_id) == user_id)
            );
        if(rows.empty()) {
            return std::optional<SavingsAccount>();
        }
        return rows.front();
    }

    static std::optional<SavingsAccount> getSavingsAccount(int id) {
        auto storage = BankDB::getStorage();
        auto rows = storage.get_all<SavingsAccount>(
            where(c(&SavingsAccount::id) == id)
            );
        if(rows.empty()) {
            return std::optional<SavingsAccount>();
        }
        return rows.front();
    }

};

#endif // FETCHER_H
