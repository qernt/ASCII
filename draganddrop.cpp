#include "draganddrop.h"
#include "ui_draganddrop.h"
#include <QFileDialog>
#include <QDragEnterEvent>
#include <QMessageBox>

DragAndDrop::DragAndDrop(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DragAndDrop)
{
    ui->setupUi(this);
    setMinimumSize(100,300);
    setAcceptDrops(true);

    connect(this, &DragAndDrop::setFileUrl, this, [=](){
       ui->pushButton->setEnabled(false);
    });

    connect(this, &DragAndDrop::fileWasSelected, this, [=](){
        ui->pushButton->setEnabled(false);
    });

    setAutoFillBackground(true);
}

DragAndDrop::~DragAndDrop()
{
    delete ui;
}

void DragAndDrop::on_pushButton_clicked()
{
    QString fileUrl = nullptr;
    fileUrl = QFileDialog::getOpenFileName(this, tr("Open File"),"/Desktop",tr("Images (*.jpeg *.jpg *.png *.HEIC)"));

    if(fileUrl != nullptr)
        emit setFileUrl(&fileUrl);
}

void DragAndDrop::activatePoles()
{
    ui->pushButton->setEnabled(true);
}

void DragAndDrop::dragEnterEvent(QDragEnterEvent *event)
{
    setBackgroundRole(QPalette::Highlight);
    event->acceptProposedAction();
    emit mimeChanged(event->mimeData());
}

void DragAndDrop::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}

void DragAndDrop::dragLeaveEvent(QDragLeaveEvent *event)
{
    clear();
}

void DragAndDrop::dropEvent(QDropEvent *event)
{
    setBackgroundRole(QPalette::NoRole);

    const QMimeData *mimeData = event->mimeData();

    if(mimeData->hasUrls())
    {
        QList<QUrl> urlList = mimeData->urls();

        if(isValidFormat(urlList.at(0).path().toStdString()))
            emit fileWasSelected(urlList.at(0).path());
        else
            QMessageBox::critical(nullptr, "Error", "Bad file format");
    }else
        QMessageBox::critical(nullptr, "Error", "Error");
}

void DragAndDrop::clear()
{
    setBackgroundRole(QPalette::NoRole);
    emit mimeChanged();
}

bool DragAndDrop::isValidFormat(const std::string &filePath)
{
    std::string fileExtension = filePath.substr(filePath.find_last_of(".") + 1);
    return (fileExtension == "jpg" || fileExtension == "png" || fileExtension == "jpeg" || fileExtension == "HEIC");
}




