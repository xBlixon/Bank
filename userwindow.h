#ifndef USERWINDOW_H
#define USERWINDOW_H
#include "user.h"
#include <QWidget>
#include "personalaccount.h"

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

private:
    void openPersonalAccount();
};

#endif // USERWINDOW_H
