#include "userwindow.h"
#include "ui_userwindow.h"

UserWindow::UserWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserWindow)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::Window);
    this->setWindowTitle("User Menu");
}

UserWindow::~UserWindow()
{
    delete ui;
}
