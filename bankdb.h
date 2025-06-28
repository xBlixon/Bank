#include "sqlite_orm/sqlite_orm.h"
#include "user.h"
using namespace sqlite_orm;

#ifndef BANKDB_H
#define BANKDB_H

class BankDB {
public:
    static auto connect(const std::string& path) {
        return make_storage(path,
                        make_table("users",
                                   make_column("id", &User::id),
                                   make_column("username", &User::username)
                                )
                        );
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
