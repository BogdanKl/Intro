#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtCore/QTimer>
#include <QtCore/QDebug>
#include <QtCore/QByteArray>

#include <qextserialport.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    QextSerialPort *port;
    QextSerialPort *portr;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
 signals:
    void contin();

private slots:
    void on_Begin_clicked();
    void iter();
    void on_End_clicked();
    void doing();

    void on_Quit_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
