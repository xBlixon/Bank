#ifndef PERSONALACCOUNTWINDOW_H
#define PERSONALACCOUNTWINDOW_H

#include <QWidget>
#include "accountwindowbase.h"
#include "personalaccount.h"

namespace Ui {
class PersonalAccountWindow;
}

class PersonalAccountWindow : public QWidget, protected AccountWindowBase
{
    Q_OBJECT

public:
    explicit PersonalAccountWindow(PersonalAccount account, QWidget *parent = nullptr);
    ~PersonalAccountWindow();

private:
    Ui::PersonalAccountWindow *ui;
    PersonalAccount account;
    void deposit();
    void withdraw();
    void transferToPersonal();
    void transferToSavings();
    void updateBalance() override;
    int sanitizeAmount() override;
};

#endif // PERSONALACCOUNTWINDOW_H
