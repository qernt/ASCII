#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "Magick++.h"


QString file = nullptr;

bool invert = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Select a file");

    dragDropWidget = new DragAndDrop(this);
    ui->verticalLayout->addWidget(dragDropWidget);

    //Quality
    ui->qualityCombo->addItem(tr("Low detail"), MainWindow::Low);
    ui->qualityCombo->addItem(tr("Average detail"), MainWindow::Average);
    ui->qualityCombo->addItem(tr("High detail"), MainWindow::High);
    ui->qualityCombo->addItem(tr("Excellent detail"), MainWindow::Excellent);

    //Language
    ui->languageCombo->addItem(tr("English"));
    ui->languageCombo->addItem(tr("Čeština"));
    ui->languageCombo->addItem(tr("Русский"));

    ui->qualityCombo->setEnabled(false);
    ui->convertButton->setEnabled(false);
    ui->inverseCheckBox->setEnabled(false);

    connect(dragDropWidget, &DragAndDrop::setFileUrl, this, &MainWindow::setFileUrl);
    connect(dragDropWidget, &DragAndDrop::fileWasSelected, this, &MainWindow::fileWasSelected);
    connect(dragDropWidget, &DragAndDrop::setFileUrl, this, [=]{
        this->setWindowTitle("Start the conversion");
    });
    connect(dragDropWidget, &DragAndDrop::fileWasSelected, this, [=]{
        this->setWindowTitle("Start the conversion");
    });

    connect(this, &MainWindow::endOfConversion, this, &MainWindow::deactivatePoles);
    connect(this, &MainWindow::endOfConversion, dragDropWidget, &DragAndDrop::activatePoles);
    connect(this, &MainWindow::endOfConversion, this, [=](){
        this->setWindowTitle("Select a file");
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::activatePoles()
{
    ui->qualityCombo->setEnabled(true);
    ui->convertButton->setEnabled(true);
    ui->inverseCheckBox->setEnabled(true);
}

void MainWindow::deactivatePoles()
{
    ui->qualityCombo->setEnabled(false);
    ui->convertButton->setEnabled(false);
    ui->inverseCheckBox->setEnabled(false);
}

void MainWindow::setFileUrl(const QString *fileUrl)
{
    activatePoles();
    file = *fileUrl;
}

void MainWindow::fileWasSelected(const QString fileUrl)
{
    activatePoles();
    file = fileUrl;
}


void MainWindow::on_convertButton_clicked()
{
    dragDropWidget->hide();
    statusBar = new StatusBar(this);
    ui->verticalLayout->addWidget(statusBar);
    QApplication::processEvents();

    Magick::InitializeMagick("");

    Magick::Image image(file.toStdString());

    Magick::ColorRGB color;

    Magick::Geometry newSize;

    double pixelRed;
    double pixelGreen;
    double pixelBlue;

    int average;

    switch(ui->qualityCombo->currentData().toInt())
    {
        case MainWindow::Low:
            newSize = Magick::Geometry(320, 240);
            break;

        case MainWindow::Average:
            newSize = Magick::Geometry(640, 480);
            break;

        case MainWindow::High:
            newSize = Magick::Geometry(720, 576);
            break;

        case MainWindow::Excellent:
            newSize = Magick::Geometry(1280, 720);
            break;
    }

    image.resize(newSize);

    size_t width = image.columns();
    size_t height = image.rows();

    Magick::Image outputImage(Magick::Geometry(width * 14, height * 12), Magick::Color("white"));
    outputImage.font("/Users/alexeygolubev/Documents/programming/ASCII-Converter-UI/consolas.ttf");
    outputImage.fontPointsize(12);
    std::string ASCIItext = "";

    int progress = 0;

    for(int h = 0; h < height; h++)
    {
        ASCIItext = "";
        for(int w = 0; w < width; w++)
        {

            color = image.pixelColor(w, h);
            pixelRed = color.red();
            pixelGreen = color.green();
            pixelBlue = color.blue();

            average = static_cast<int>((pixelRed + pixelBlue + pixelGreen) * 255 / 3);

            if(average > 255)
                average = 255;
            if(average < 0)
                average = 0;

            if(invert)
            {
                if(average >= 0 && average <= 16)
                {
                    ASCIItext += " ";
                }else if(average >= 17 && average <= 32)
                {
                    ASCIItext += ".";
                }else if(average >= 33 && average <= 48)
                {
                    ASCIItext += "-";
                }else if(average >= 49 && average <= 64)
                {
                    ASCIItext += "~";
                }else if(average >= 65 && average <= 80)
                {
                    ASCIItext += ":";
                }else if(average >= 81 && average <= 96)
                {
                    ASCIItext += ";";
                }else if(average >= 97 && average <= 112)
                {
                    ASCIItext += "=";
                }else if(average >= 113 && average <= 128)
                {
                    ASCIItext += "+";
                }else if(average >= 129 && average <= 144)
                {
                    ASCIItext += "*";
                }else if(average >= 145 && average <= 160)
                {
                    ASCIItext += "#";
                }else if(average >= 161 && average <= 176)
                {
                    ASCIItext += "%";
                }else if(average >= 177 && average <= 192)
                {
                    ASCIItext += "@";
                }else if(average >= 193 && average <= 208)
                {
                    ASCIItext += "&";
                }else if(average >= 209 && average <= 224)
                {
                    ASCIItext += "$";
                }else if(average >= 225 && average <= 240)
                {
                    ASCIItext += "!";
                }else if(average >= 241 && average <= 255)
                {
                    ASCIItext += "#";
                }
            }else
            {
                if(average >= 0 && average <= 16)
                {
                    ASCIItext += "#";
                }else if(average >= 17 && average <= 32)
                {
                    ASCIItext += "!";
                }else if(average >= 33 && average <= 48)
                {
                    ASCIItext += "$";
                }else if(average >= 49 && average <= 64)
                {
                    ASCIItext += "&";
                }else if(average >= 65 && average <= 80)
                {
                    ASCIItext += "@";
                }else if(average >= 81 && average <= 96)
                {
                    ASCIItext += "\%";
                }else if(average >= 97 && average <= 112)
                {
                    ASCIItext += "#";
                }else if(average >= 113 && average <= 128)
                {
                    ASCIItext += "*";
                }else if(average >= 129 && average <= 144)
                {
                    ASCIItext += "+";
                }else if(average >= 145 && average <= 160)
                {
                    ASCIItext += "=";
                }else if(average >= 161 && average <= 176)
                {
                    ASCIItext += ";";
                }else if(average >= 177 && average <= 192)
                {
                    ASCIItext += ":";
                }else if(average >= 193 && average <= 208)
                {
                    ASCIItext += "~";
                }else if(average >= 209 && average <= 224)
                {
                    ASCIItext += "-";
                }else if(average >= 225 && average <= 240)
                {
                    ASCIItext += ".";
                }else if(average >= 241 && average <= 255)
                {
                    ASCIItext += " ";
                }
            }
            ASCIItext += " ";
        }

        progress = h * 100 / height;
        this->setWindowTitle(QString::number(progress) + "%");
        statusBar->changeStatusBarValue(progress);

        Magick::DrawableText drawableText(0, h * 12, ASCIItext);

        outputImage.draw(drawableText);

        QApplication::processEvents();
    }

    QString direcotry = directoryRequest();
    if(direcotry != nullptr)
        outputImage.write(direcotry.toStdString());

    delete statusBar;
    dragDropWidget->show();
    emit endOfConversion();
}

QString MainWindow::directoryRequest()
{
    directoryWidget = new DirectorySelection(this);
    directoryWidget->setWindowModality(Qt::WindowModal);
    directoryWidget->show();

    while (directoryWidget->isVisible())
        QCoreApplication::processEvents();

    QString selectedDirectory = directoryWidget->getSelectedDirectory();

    delete directoryWidget;

    return selectedDirectory;
}


void MainWindow::on_inverseCheckBox_toggled(bool checked)
{
    invert = checked;
}


