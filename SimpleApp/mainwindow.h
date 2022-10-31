#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include <QByteArray>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onScanContextsButtonClicked();
    void onSelectContextButtonClicked();

    void onScanDevicesButtonClicked();
    void onSelectDevicesButtonClicked();

    void onScanChannelsButtonClicked();
    void onSelectChannelButtonClicked();

    void onScanAttributesButtonClicked();
    void onSelectAttributeButtonClicked();

    void onReadButtonClicked();
    void onWriteButtonClicked();

private:
    Ui::MainWindow *ui;
    struct iio_scan_context *scanCtx = NULL;
    struct iio_context_info **ctxInfo = NULL;
    struct iio_context *ctx = NULL;
    struct iio_device *dev = NULL;
    struct iio_channel *chn = NULL;
};
#endif // MAINWINDOW_H
