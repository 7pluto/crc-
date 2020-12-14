#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QFontDialog"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    EthernetCrc ec;
    QString str;
    uchar_8 tx_data[1056];
    int  _dataLen;
    unsigned int crc_data;
    ui->label->clear();
    str = ui->textEdit->toPlainText();
    ec.format_conversion(str, tx_data, _dataLen);
    //ec.gen_CRC32_TAB(ec.Table1);//生成CRC32多项式表
    //为了结果比较，直接指定0x04c11db7
    crc_data = ec.getCrc32CheckSum(tx_data, _dataLen, 0x04c11db7);
    ui->label->setText(QString::number(crc_data, 16));
    //printf("CRC          : %08x\n", crc_data);

}
