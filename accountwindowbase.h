#ifndef ACCOUNTWINDOWBASE_H
#define ACCOUNTWINDOWBASE_H
#include "AccountTypes.h"

class AccountWindowBase
{
public:
    AccountWindowBase();

protected:
    // virtual void setBalance(double newBalance) = 0;
    virtual void updateBalance() = 0;

    void depositFunds(int user_id, AccountType type, int amount);
    void withdrawFunds(int user_id, AccountType type, int amount);
    void transferFunds(int sender_id, AccountType sender_type, int receiver_id, AccountType receiver_type, int amount);

    virtual int sanitizeAmount() = 0;
};

#endif // ACCOUNTWINDOWBASE_H
