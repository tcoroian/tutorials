#include "alternativewindow.h"
#include "ui_alternativewindow.h"

AlternativeWindow::AlternativeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AlternativeWindow)
{
    ui->setupUi(this);
}

AlternativeWindow::~AlternativeWindow()
{
    delete ui;
}
