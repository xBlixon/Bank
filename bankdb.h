#ifndef BANKDB_H
#define BANKDB_H
#include "sqlite_orm/sqlite_orm.h"
#include "user.h"
#include "personalaccount.h"
using namespace sqlite_orm;

class BankDB {
public:
    static auto getStorage() {
        auto storage = make_storage(path,
                                    make_table("users",
                                               make_column("id", &User::id, primary_key()),
                                               make_column("username", &User::username),
                                               make_column("password", &User::password)
                                               ),
                                    make_table("personal_account",
                                               make_column("id", &PersonalAccount::id, primary_key()),
                                               make_column("user_id", &PersonalAccount::user_id),
                                               make_column("balance", &PersonalAccount::balance),
                                               foreign_key(&PersonalAccount::user_id).references(&User::id),
                                               unique(&PersonalAccount::user_id)
                                               )
                                    );
        storage.sync_schema();
        return storage;
    }
    static void setPath(const std::string& path) {
        BankDB::path = path;
    }
    static std::string getPath() {
        return BankDB::path;
    }


private:
    BankDB();
    BankDB(const BankDB&) = delete;
    BankDB& operator=(const BankDB&) = delete;
    static std::string path;
};

std::string BankDB::path = "";

#endif // BANKDB_H
