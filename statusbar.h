#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QWidget>

namespace Ui {
class StatusBar;
}

class StatusBar : public QWidget
{
    Q_OBJECT

public:
    explicit StatusBar(QWidget *parent = nullptr);
    ~StatusBar();

private:
    Ui::StatusBar *ui;

public:
    void changeStatusBarValue(int value);
};

#endif // STATUSBAR_H
