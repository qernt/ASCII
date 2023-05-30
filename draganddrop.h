#ifndef DRAGANDDROP_H
#define DRAGANDDROP_H

#include <QWidget>
#include <QMimeData>


namespace Ui {
class DragAndDrop;
}

class DragAndDrop : public QWidget
{
    Q_OBJECT

public:
    explicit DragAndDrop(QWidget *parent = nullptr);
    ~DragAndDrop();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DragAndDrop *ui;

signals:
    void setFileUrl(const QString *fileUrl);

    void mimeChanged(const QMimeData *mimeData = nullptr);

    void fileWasSelected(const QString fileUrl);

public slots:
    void activatePoles();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    void clear();
    bool isValidFormat(const std::string &filePath);

public:
    QString imagePath;
};

#endif // DRAGANDDROP_H
