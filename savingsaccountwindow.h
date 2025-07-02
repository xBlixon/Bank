#ifndef SAVINGSACCOUNTWINDOW_H
#define SAVINGSACCOUNTWINDOW_H

#include <QWidget>
#include "accountwindowbase.h"
#include "savingsaccount.h"

namespace Ui {
class SavingsAccountWindow;
}

class SavingsAccountWindow : public QWidget, protected AccountWindowBase
{
    Q_OBJECT

public:
    explicit SavingsAccountWindow(SavingsAccount account, QWidget *parent = nullptr);
    ~SavingsAccountWindow();

private:
    Ui::SavingsAccountWindow *ui;

    SavingsAccount account;
    void deposit();
    void withdraw();
    void transferToPersonal();
    void transferToSavings();
    void updateBalance() override;
    int sanitizeAmount() override;
    void giveInterest();

};

#endif // SAVINGSACCOUNTWINDOW_H
