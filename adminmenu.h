#ifndef ADMINMENU_H
#define ADMINMENU_H

#include <QWidget>

namespace Ui {
class AdminMenu;
}

class AdminMenu : public QWidget
{
    Q_OBJECT

public:
    explicit AdminMenu(QWidget *parent = nullptr);
    ~AdminMenu();

private:
    Ui::AdminMenu *ui;
    void addUser();
    void addAccount();
};

#endif // ADMINMENU_H
