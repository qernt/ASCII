#include "directoryselection.h"
#include "ui_directoryselection.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>

DirectorySelection::DirectorySelection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DirectorySelection)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() | Qt::Window);
    setFixedSize(300,160);
}

DirectorySelection::~DirectorySelection()
{
    delete ui;
}

QString DirectorySelection::getSelectedDirectory()
{
    return selectedDirectory;
}

void DirectorySelection::on_okButton_clicked()
{
    QDir directory(ui->selectDirectoryLineEdit->text());
    if(directory.exists() && ui->nameLineEdit->text() != "" && ui->selectDirectoryLineEdit->text() != nullptr)
    {
        selectedDirectory = ui->selectDirectoryLineEdit->text() + "/" + ui->nameLineEdit->text() + ".jpeg";
        close();
    }else if(ui->nameLineEdit->text() == nullptr)
        QMessageBox::critical(nullptr, "Error", "File name not seted up");
    else
        QMessageBox::critical(nullptr, "Error", "This directory does not exist");
}


void DirectorySelection::on_selectDirectoryButton_clicked()
{
    ui->selectDirectoryLineEdit->setText(QFileDialog::getExistingDirectory(this, tr("Select Directory"), QDir::homePath()));
}


void DirectorySelection::on_cancelButton_clicked()
{
    selectedDirectory = nullptr;
    close();
}

