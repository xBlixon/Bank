#include "accountwindow.h"
#include "ui_accountwindow.h"

AccountWindow::AccountWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AccountWindow)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::Window);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

AccountWindow::~AccountWindow()
{
    delete ui;
}
