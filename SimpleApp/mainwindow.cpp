#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iio.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTextStream ts(stdout);

    connect(ui->readAttrButton, SIGNAL (clicked()), this, SLOT (onReadButtonClicked()));

    connect(ui->scanContextsButton, SIGNAL (clicked()), this, SLOT (onScanContextsButtonClicked()));
    connect(ui->selectContextButton, SIGNAL (clicked()), this, SLOT (onSelectContextButtonClicked()));

    connect(ui->scanDevicesButton, SIGNAL (clicked()), this, SLOT (onScanDevicesButtonClicked()));
    connect(ui->selectDeviceButton, SIGNAL (clicked()), this, SLOT (onSelectDevicesButtonClicked()));

    connect(ui->scanChannelsButton, SIGNAL (clicked()), this, SLOT (onScanChannelsButtonClicked()));
    connect(ui->selectChannelButton, SIGNAL (clicked()), this, SLOT (onSelectChannelButtonClicked()));

    connect(ui->scanAttributesButton, SIGNAL (clicked()), this, SLOT (onScanAttributesButtonClicked()));
    connect(ui->selectAttributeButton, SIGNAL (clicked()), this, SLOT (onSelectAttributeButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onReadButtonClicked() {
    QString attribute = ui->attributeField->text();
    QByteArray ba = attribute.toLocal8Bit();
    char *toFind = ba.data();

    if (attribute.isEmpty()) {
        ui->attributeField->setText("Please input an attribute");
        return;
    }

    char attrValue[32];
    iio_channel_attr_read(chn, toFind, attrValue, 32);

    ui->valueField->setText(attrValue);
}

void MainWindow::onWriteButtonClicked() {

}

void MainWindow::onScanContextsButtonClicked() {
    ui->contextListWidget->clear();

    scanCtx = iio_create_scan_context("local,usb,ip", 0);
    if (scanCtx == NULL) {
        ui->contextListWidget->addItem("No contexts were found");
        return;
    }

    iio_scan_context_get_info_list(scanCtx, &ctxInfo);
    if (ctxInfo == NULL) {
        ui->contextListWidget->addItem("No context info was found");
        return;
    }

    int i = 0;
    while (ctxInfo[i] != NULL) {
        ui->contextListWidget->addItem(iio_context_info_get_uri(ctxInfo[i]));
        i++;
    }
}

void MainWindow::onSelectContextButtonClicked() {
    QListWidgetItem *selectedItem = ui->contextListWidget->currentItem();

    if (selectedItem == NULL) {
        ui->contextField->setText("Please select a context");
        return;
    }

    QString context = selectedItem->text();
    QByteArray ba = context.toLocal8Bit();
    char *toFind = ba.data();

    ctx = iio_create_context_from_uri(toFind);
    if (ctx == NULL) {
        ui->contextField->setText("No context was found");
        return;
    }
    ui->contextField->setText(iio_context_get_name(ctx));

    onScanDevicesButtonClicked();
}

void MainWindow::onScanDevicesButtonClicked() {
    ui->deviceListWidget->clear();

    if (ctx == NULL) {
        ui->deviceListWidget->addItem("No context was selected");
        return;
    }

    int devCount = iio_context_get_devices_count(ctx);
    for (int i = 0; i < devCount; i++) {
        auto *device = iio_context_get_device(ctx, i);
        ui->deviceListWidget->addItem(iio_device_get_name(device));
    }
}

void MainWindow::onSelectDevicesButtonClicked() {
    QListWidgetItem *selectedItem = ui->deviceListWidget->currentItem();

    if (selectedItem == NULL) {
        ui->deviceField->setText("Please select a device");
        return;
    }

    QString context = selectedItem->text();
    QByteArray ba = context.toLocal8Bit();
    char *toFind = ba.data();

    dev = iio_context_get_device(ctx, ui->deviceListWidget->row(selectedItem));
    if (dev == NULL) {
        ui->deviceField->setText("No device was found");
        return;
    }
    ui->deviceField->setText(toFind);
    onScanChannelsButtonClicked();
}

void MainWindow::onScanChannelsButtonClicked() {
    ui->channelListWidget->clear();

    if (dev == NULL) {
        ui->channelListWidget->addItem("No context was selected");
        return;
    }

    int chnCount = iio_device_get_channels_count(dev);
    for (int i = 0; i < chnCount; i++) {
        auto *channel = iio_device_get_channel(dev, i);
        ui->channelListWidget->addItem(iio_channel_get_id(channel));
    }
}

void MainWindow::onSelectChannelButtonClicked() {
    QListWidgetItem *selectedItem = ui->channelListWidget->currentItem();

    if (selectedItem == NULL) {
        ui->channelField->setText("Please select a channel");
        return;
    }

    QString context = selectedItem->text();
    QByteArray ba = context.toLocal8Bit();
    char *toFind = ba.data();

    chn = iio_device_get_channel(dev, ui->channelListWidget->row(selectedItem));
    if (chn == NULL) {
        ui->deviceField->setText("No channel was found");
        return;
    }

    ui->channelField->setText(toFind);
    onScanAttributesButtonClicked();
}

void MainWindow::onScanAttributesButtonClicked() {
    ui->attributeListWidget->clear();

    if (chn == NULL) {
        ui->attributeListWidget->addItem("No channel was selected");
        return;
    }

    int attrCount = iio_channel_get_attrs_count(chn);
    for (int i = 0; i < attrCount; i++) {
        auto *attribute = iio_channel_get_attr(chn, i);
        ui->attributeListWidget->addItem(attribute);
    }
}

void MainWindow::onSelectAttributeButtonClicked() {
    QListWidgetItem *selectedItem = ui->attributeListWidget->currentItem();

    if (selectedItem == NULL) {
        ui->attributeField->setText("Please select an attribute");
        return;
    }

    QString context = selectedItem->text();
    QByteArray ba = context.toLocal8Bit();
    char *toFind = ba.data();

    auto *attr = iio_channel_get_attr(chn, ui->attributeListWidget->row(selectedItem));
    if (attr == NULL) {
        ui->attributeField->setText("No attribute was found");
        return;
    }

    ui->attributeField->setText(toFind);
    onReadButtonClicked();
}
