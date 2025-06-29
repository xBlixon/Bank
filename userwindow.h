#include "user.h"

#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QWidget>

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
};

#endif // USERWINDOW_H
