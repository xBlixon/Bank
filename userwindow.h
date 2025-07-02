#ifndef USERWINDOW_H
#define USERWINDOW_H
#include "user.h"
#include <QWidget>
#include "personalaccount.h"
#include "savingsaccount.h"

namespace Ui {
class UserWindow;
}

class UserWindow : public QWidget
{
    Q_OBJECT

public:
    explicit UserWindow(User& user, QWidget *parent = nullptr);
    ~UserWindow();

private:
    User user;
    Ui::UserWindow *ui;
    std::optional<PersonalAccount> personal_account;
    std::optional<SavingsAccount> savings_account;

    void fetchAccounts();
    void openPersonalAccount();
    void openSavingsAccount();
};

#endif // USERWINDOW_H
