#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::vector<User> logged_users;

public:
    void loadDatabase();
    void loginUser();
    bool isUserLoggedIn(User& user);

protected:
    void closeEvent(QCloseEvent *event) override;
};
#endif // MAINWINDOW_H
