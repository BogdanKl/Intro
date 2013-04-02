#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <qextserialport.h>

#include <QMainWindow>
#include <QLineEdit>
#include <QtCore/QByteArray>
#include <QtCore/QDebug>

namespace Ui {
class MainWindow;
}
extern int m_value;
extern int size;
extern int result;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:

    QextSerialPort *port;
    QByteArray arr;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void contin();
    
private slots:
    void on_lineEdit_textChanged(const QString &arg1);
    void on_Quit_clicked();
    void on_End_clicked();
    void on_Begin_clicked();
    void onDataAvailable();
    void make();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
