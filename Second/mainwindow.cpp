#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qextserialport.h>

#include <QtCore/QString>
#include <QtCore/QByteArray>
#include <QtCore/QDebug>
#include <QtCore/QObject>

int m_value = 0;
int size = 8;
int result;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_value = 4;
    port = new QextSerialPort("COM4");
    //port->setBaudRate(BAUD19200);
    //port->setFlowControl(FLOW_OFF);
    //port->setParity(PAR_NONE);
    //port->setDataBits(DATA_8);
    //port->setStopBits(STOP_2);
    port->open(QIODevice::ReadWrite);
    qDebug() << port->isOpen();
    qDebug() << port->readAll();
    QObject::connect(this,SIGNAL(contin()),this,SLOT(make()));
    arr.clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    ui->lineEdit->setText(arg1);
}

void MainWindow::on_Quit_clicked()
{
    this->close();
}

void MainWindow::on_End_clicked()
{
    ui->lineEdit->setText(QString::number(result));
    m_value = 0;
}
void MainWindow::make()
{
    while (port->waitForBytesWritten(2000)){
      connect(port,SIGNAL(bytesWritten(qint64)),this,SLOT(onDataAvailable()));
    }
    m_value ++;
    qDebug() << m_value;
    if (m_value < 100)
    {
      emit contin();
    }
    {
        m_value = 0;
    }
}

void MainWindow::on_Begin_clicked()
{
    emit contin();
}
void MainWindow::onDataAvailable() {
    char buff[1024];
        int numBytes;
        numBytes = port->bytesAvailable();
        qDebug() << numBytes;
        if(numBytes > 0)
        {
            if(numBytes > 1024)
                 numBytes = 1024;
            int i = port->read(buff, numBytes);
            buff[i] = '\0';
            QString msg = buff;
            //qDebug(msg);
            qDebug("bytes available: %d", numBytes);
            qDebug("received: %d", i);
      }
 }
