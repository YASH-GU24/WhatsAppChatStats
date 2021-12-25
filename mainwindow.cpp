#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include <fstream>
#include <iostream>
#include <QPair>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(166, 0, 86));
    gradient.setColorAt(0.38, QColor(201, 42, 125));
    gradient.setColorAt(1, QColor(255, 64, 163));



    //////////////////////////////PUT PATH TO EXPORTED CHAT HER////////////////////////////////////////////

     newfile.open("/home/yash/Downloads/WhatsApp Chat with GFG -Unofficial CM 2021 🔥.txt",std::ios::in);





     ////////////////////////////////////////////////////////////////////////////////////////////////////




    myBars = new QCPBars(ui->customPlot->yAxis, ui->customPlot->xAxis);
    // now we can modify properties of myBars:
    myBars->setName("Bars Series 1");
    myBars->setBrush(QBrush(gradient));
    connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    mDataTimer.start(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::timerSlot()
{
    std::string tp;
    if(getline(newfile, tp)){
          if(48<=int(tp[0]) && int(tp[0])<=57 && 48<=int(tp[1]) && int(tp[1])<=57 && tp[2]=='/')
          {
              std::string date="";
              int i=0;
              std::string name="";

             while(tp[i]!=',' && i<tp.length())
             {
                date=date+tp[i];
                 i++;
              }
              while(tp[i]!='-' && i<tp.length())
              {
                i++;
              }
              i++;
              while(tp[i]!=':' &&i<tp.length())
              {
                name=name+tp[i];
                 i++;
              }
            if(i!=tp.length()){
            QString Name=QString::fromStdString(name);
            QString Date=QString::fromStdString(date);
//            qDebug()<<Name<<" "<<Date;
            if(Name==" .")
                Name="Yash Gupta";
                ma[Name]++;
                ui->date->setText("Date: "+Date);
                msgCount++;
                ui->msg->setText("Total Message Count: " + QString::number(msgCount));
          }
    }
    }
    QVector<double> keyData;
    qint64 n=0;


    QVector<double> valueData;
    QMapIterator<QString, double> i(ma);
    QVector<QString> labels;
    QList<QPair<QString,double>> inv;

    while (i.hasNext()  ) {
        i.next();
        if(n<10)
        keyData<<n;
        inv.append({i.key(),i.value()});

        n++;
    }
    std::sort(std::begin(inv), std::end(inv),[](const QPair<QString,double> &l,const QPair<QString,double> &r){
        return l.second<r.second;
    });
    QListIterator<QPair<QString,double>> itr(inv);
    itr.toBack();
    qint64 c=10;
    while (itr.hasPrevious() && c--)
    {
        QPair<QString,double> p=itr.previous();

        valueData<<p.second;
        labels<<p.first;
    }
    ui->top->setText("Top Member:"+inv.rbegin()->first + " With Message Count:" +QString::number(inv.rbegin()->second));

    std::reverse(keyData.begin(),keyData.end());
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(keyData, labels);
    ui->customPlot->yAxis->setTicker(textTicker);
    myBars->setData(keyData, valueData);
    ui->customPlot->rescaleAxes();
    ui->customPlot->replot();
}

