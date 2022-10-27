#ifndef ALTERNATIVEWINDOW_H
#define ALTERNATIVEWINDOW_H

#include <QMainWindow>

namespace Ui {
class AlternativeWindow;
}

class AlternativeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AlternativeWindow(QWidget *parent = nullptr);
    ~AlternativeWindow();

private:
    Ui::AlternativeWindow *ui;
};

#endif // ALTERNATIVEWINDOW_H
