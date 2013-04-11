#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qextserialport.h>

#include <QtCore/QString>
#include <QtCore/QByteArray>
#include <QtCore/QDebug>
#include <QtCore/QObject>

int m_value = 0;
char *result;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    port = new QextSerialPort("COM3",QextSerialPort::Polling);
    qDebug() << port->baudRate();
    qDebug() << port->dataBits();
    m_value = 0;
    port -> open(QIODevice::WriteOnly);
    portr = new QextSerialPort("COM5",QextSerialPort::Polling);
    portr-> open(QIODevice::ReadOnly);
    qDebug() << portr->isOpen();
    qDebug() << port->isOpen();
    qDebug() << port->openMode();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::iter()
{
    int i = port -> write("aba");
    if (i <= 0)
    {
        qDebug("Error");
    }
    if (m_value <4 )
    {
        m_value++;
        //MainWindow::doing();
        connect(port,SIGNAL(bytesWritten(qint64)),this,SLOT(doing()));
    }
    else
    {

    }
}

void MainWindow::on_Begin_clicked()
{
    char * str = "1000" ;
    int num;
    int i = port->write(str,qstrlen(str));
    qDebug("I= %d",i);
    m_value++;
    //MainWindow::iter();
    connect(port,SIGNAL(bytesWritten(qint64)),this,SLOT(doing()));

}

void MainWindow::on_End_clicked()
{
    ui->lineEdit->setText(result);
    m_value = 0;
}
void MainWindow::doing()
{
    portr->waitForBytesWritten(-1);
    char buff[1024];
    int numBytes;
    numBytes = portr->bytesAvailable();
    qDebug("numBytes= %d", numBytes);
    if(numBytes > 0)
    {
        if(numBytes > 1024)
            numBytes = 1024;
        int i = portr->read(buff, numBytes);
        buff[i] = '\0';
        result = buff;
        qDebug("bytes available: %d", numBytes);
        qDebug("received: %d", i);
        qDebug("buff = %s", buff);
    }
    MainWindow::iter();
    connect(portr,SIGNAL(readChannelFinished()),this,SLOT(iter()));
}

void MainWindow::on_Quit_clicked()
{
    this->close();
}
