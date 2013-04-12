
#include <QtCore/QString>
#include <QtCore/QByteArray>
#include <QtCore/QDebug>
#include <QtCore/QObject>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qextserialport.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mPortW = new QextSerialPort("COM3",QextSerialPort::Polling);
    mPortW -> open(QIODevice::WriteOnly);
    mPortR = new QextSerialPort("COM5",QextSerialPort::Polling);
    mPortR-> open(QIODevice::ReadOnly);
    mTimerR = new QTimer(this);
    mTimerW = new QTimer(this);
    mNumIteration = 0;
    mTimerR->setInterval(1000);
    mTimerW->setInterval(1000);
    connect(mTimerR, SIGNAL(timeout()), this, SLOT(writting()));
    connect(mTimerW, SIGNAL(timeout()), this, SLOT(reading()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::writting()
{
    if (mNumIteration < 100)
    {
        mNumIteration++;
        int i = mPortW -> write(QByteArray::number(mNumIteration));
        if (i <= 0)
        {
            qDebug("Error");
        }
        else
        {
            mTimerW->start();
        }
    }
}

void MainWindow::on_Begin_clicked()
{
    qDebug("Begin");
    mTimerW->start();
}

void MainWindow::on_End_clicked()
{
    ui->lineEdit->setText(mResult);
    mTimerR->stop();
    mTimerW->stop();
    //mTimerR->disconnect(mTimerR, SIGNAL(timeout()), this, SLOT(writting()));
    //mTimerW->disconnect(mTimerW, SIGNAL(timeout()), this, SLOT(reading()));
    mNumIteration = 0;
}

void MainWindow::reading()
{
    char buff[1024];
    int numBytes;
    numBytes = mPortR->bytesAvailable();
    qDebug("numBytes= %d", numBytes);
    if (numBytes > 0)
    {
        if(numBytes > 1024)
            numBytes = 1024;
        int i = mPortR->read(buff, numBytes);
        buff[i] = '\0';
        qDebug("bytes available: %d", numBytes);
        qDebug("received: %d", i);
        qDebug("buff = %s", buff);
    }
    mTimerR->start();
}

void MainWindow::on_Quit_clicked()
{
    this->close();
}

