#include "statusbar.h"
#include "ui_statusbar.h"

StatusBar::StatusBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusBar)
{
    ui->setupUi(this);
    setMinimumSize(100,300);
}

StatusBar::~StatusBar()
{
    delete ui;
}

void StatusBar::changeStatusBarValue(int value)
{
    ui->progressBar->setValue(value);
    ui->label->setText(QString::number(value) + " %");
}

