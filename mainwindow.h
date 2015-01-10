#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtCore/QCoreApplication>
#include <QtCore>
#include <QFile>
#include <QDebug>
#include <sstream>

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int sort(QString* a, int n, QString na);
    int sortsub(QString* a, int n, QString na, QString* subl, QString subb);
    QString deleteduplicates(QString a[22], int n);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
