#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qextserialport.h>

#include <QtGui/QMainWindow>0
#include <QTimer>
#include <QDebug>
#include <QByteArray>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    QextSerialPort *port;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTimer *t;
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
