#ifndef FETCHER_H
#define FETCHER_H
#include "bankdb.h"
#include "personalaccount.h"

class Fetcher
{
public:
    static PersonalAccount getPersonalAccountFromUserId(int user_id) {
        auto storage = BankDB::getStorage();
        return storage.get_all<PersonalAccount>(
            where(c(&PersonalAccount::user_id) == user_id)
            ).front();
    }

    static PersonalAccount getPersonalAccount(int id) {
        auto storage = BankDB::getStorage();
        return storage.get_all<PersonalAccount>(
            where(c(&PersonalAccount::id) == id)
            ).front();
    }

};

#endif // FETCHER_H
