#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <fstream>
#include <iostream>
#include <QMainWindow>
#include <QTimer>
#include "qcustomplot.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
  void timerSlot();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::fstream newfile;
    QMap <QString,double> ma;
      QTimer mDataTimer;
      qlonglong msgCount=0;
      qint64 i=0;
     QCPBars *myBars;
};
#endif // MAINWINDOW_H
