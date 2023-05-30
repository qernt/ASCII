#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "draganddrop.h"
#include "directoryselection.h"
#include "statusbar.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    enum Quality{Low, Average, High, Excellent};

private:
    void activatePoles();
    void deactivatePoles();

private:
    Ui::MainWindow *ui;
    DragAndDrop *dragDropWidget;
    DirectorySelection *directoryWidget;
    StatusBar *statusBar;
    Quality quality;

private slots:
    void setFileUrl(const QString *fileUrl);
    void fileWasSelected(const QString fileUrl);
    void on_convertButton_clicked();
    QString directoryRequest();

    void on_inverseCheckBox_toggled(bool checked);


signals:
    void endOfConversion();
};
#endif // MAINWINDOW_H
