#ifndef DIRECTORYSELECTION_H
#define DIRECTORYSELECTION_H

#include <QWidget>

namespace Ui {
class DirectorySelection;
}

class DirectorySelection : public QWidget
{
    Q_OBJECT

public:
    explicit DirectorySelection(QWidget *parent = nullptr);
    ~DirectorySelection();

public:
    QString getSelectedDirectory();

private slots:
    void on_okButton_clicked();

    void on_selectDirectoryButton_clicked();

    void on_cancelButton_clicked();

public:
    bool isDirectoryExists(QString path);

private:
    Ui::DirectorySelection *ui;
    QString selectedDirectory;
};

#endif // DIRECTORYSELECTION_H
