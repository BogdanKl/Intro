#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qextserialport.h>

#include <QtCore/QString>
#include <QtCore/QByteArray>
#include <QtCore/QDebug>
#include <QtCore/QObject>

int m_value = 0;
int size = 8;
char *result;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    port = new QextSerialPort("COM3");
    port ->open(QIODevice::ReadWrite);
    qDebug() << port->isOpen();
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
    else{
    qDebug("iter, i= %d",i);
    qDebug() << "Bytes written";
    connect(port,SIGNAL(bytesWritten(qint64)),this,SLOT(doing()));
    }

}

void MainWindow::on_Begin_clicked()
{
    char * str = "100" ;
    int num;
    int i = port->write(str,qstrlen(str));
    qDebug("I= %d",i);
    str ="";
    i = port-> read(str,num);
    qDebug() << i;
    qDebug("read: str= %s",str);
    qDebug("iter");
    MainWindow::iter();

}

void MainWindow::on_End_clicked()
{
    ui->lineEdit->setText(result);
}
void MainWindow::doing()
{
    char buff[1024];
        int numBytes;
        numBytes = port->bytesAvailable();
        qDebug("numBytes= %d", numBytes);
        if(numBytes > 0)
        {
            if(numBytes > 1024)
                 numBytes = 1024;
            int i = port->read(buff, numBytes);
            buff[i] = '\0';
            result = buff;
            qDebug("bytes available: %d", numBytes);
            qDebug("received: %d", i);
      }
       connect(port,SIGNAL(readyRead()),this,SLOT(iter()));
        connect(port,SIGNAL(readChannelFinished()),this,SLOT(iter()));
}

void MainWindow::on_Quit_clicked()
{
    this->close();
}
