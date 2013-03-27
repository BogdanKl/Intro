#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <qextserialport.h>
#include <QByteArray>
#include <QtCore/QDebug>
#include <QObject>
#include <QDebug>

int m_value=0;
int size=8;
int result;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_value = 4;
    port = new QextSerialPort("COM1");
    port->setBaudRate(BAUD19200);
    port->setFlowControl(FLOW_OFF);
    port->setParity(PAR_NONE);
    port->setDataBits(DATA_8);
    port->setStopBits(STOP_2);
    port->open(QIODevice::ReadWrite);
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
    connect(port,SIGNAL(bytesWritten(size)),this,SLOT(onDataAvailable()));}
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
    arr = port->read(8);
    result = arr.toInt();
    qDebug() << result;
 }
