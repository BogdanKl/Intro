#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
 signals:
    void contin();
private:
    QextSerialPort *mPortW;
    QextSerialPort *mPortR;
    QTimer *mTimerR;
    QTimer *mTimerW;
    int mNumIteration;
    char mResult[1024];

private slots:
    void on_Begin_clicked();
    void writting();
    void on_End_clicked();
    void reading();
    void on_Quit_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
