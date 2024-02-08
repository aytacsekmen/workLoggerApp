#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTimer>
#include<QStringListModel>
#include<QDateTime>
#include<QTableWidgetItem>
#include<QTableWidget>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //ui->tableWidget->setEnabled(false);
    ui->setupUi(this);
    ui->stopButton->setEnabled(false);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    saat=  0;
    dakika=0;
    saniye=0;
    pause=true;
    running=false;
    entry_control=false;
    if(saat<10)
        place4="0";
    else
        place4="";
    if(dakika<10)
        place5="0";
    else
        place5="";
    if(saniye<10)
        place6="0";
    else
        place6="";
    this->setFixedSize(this->geometry().width(),this->geometry().height());
    QString my_formatted_string = QString("%4%1:%5%2:%6%3").arg(QString::number(saat), QString::number(dakika), QString::number(saniye),place4,place5,place6);
    ui->lcdPanel->display(my_formatted_string);
    connect(&timer,SIGNAL(timeout()),this,SLOT(showTimes()));
    ui->tableWidget->setColumnCount(2);
    QStringList newList;
    newList.append("Job Titles");
    newList.append("Hours Spent");
    ui->tableWidget->setHorizontalHeaderLabels(newList);
    //ui->tableWidget->insertColumn(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showTimes()
{
    //QTime time=QTime::;
    QString place4;
    QString place5;
    QString place6;
    if(saat<10)
        place4="0";
    else
        place4="";
    if(dakika<10)
        place5="0";
    else
        place5="";
    if(saniye<10)
        place6="0";
    else
        place6="";
    QString my_formatted_string = QString("%4%1:%5%2:%6%3").arg(QString::number(saat), QString::number(dakika), QString::number(saniye),place4,place5,place6);
    if(saniye==59)
    {
        if(dakika==59)
        {
            if(saat==23)
            {
                saat=0;
            }
            else
                saat++;
            dakika=0;
        }
        else
            dakika++;
        saniye=0;
    }
    else
    {
        saniye++;
    }

    ui->lcdPanel->display(my_formatted_string);

}

void MainWindow::on_startButton_clicked()
{

    QString text = ui->jobEntrytxt->toPlainText();
    if(text!="")
    {
        QMap<QString, QTime>::iterator it =map.find(text);



        if(it == map.end())
        {
            QTime n(saat,dakika,saniye,0);
            map[text]=n;
            ui->labelWarning->setText("");
            //list << text;
            //model->setStringList(list);
           // ui->gorevlerListView->setModel(model);
            if(!running)
            {
                timer.start(1000);
                running=true;
                ui->stopButton->setEnabled(true);
                ui->startButton->setEnabled(false);

                ui->stopButton->setText("Stop");
            }
        }
        else if(running==false)
        {
            ui->labelWarning->setText("There is already a job titled with this name.");
        }

    }
    else
    {
        ui->labelWarning->setText("Enter your job title...");
    }

    ui->tableWidget->setEnabled(false);

}

void MainWindow::on_stopButton_clicked()
{
    if(pause&&running)
    {
        timer.stop();
        pause=false;
        //
        ui->stopButton->setText("Continue");
    }
    else if(!pause&&running)
    {
        pause=true;
        timer.start(1000);
        ui->stopButton->setText("Stop");
    }
}

void MainWindow::on_resetButton_clicked()
{
    model = new QStringListModel(this);
    //QStringList* stringList=new QStringList();
    QString text = ui->jobEntrytxt->toPlainText();

    if(text!="")
    {
        model->insertRow(model->rowCount());
        QModelIndex index = model->index(model->rowCount()-1);
        model->setData(index, text);



        QTime n(saat,dakika,saniye,0);
        map[text]=n;

        QTableWidgetItem* newItemGorev=new QTableWidgetItem();
        QTableWidgetItem* newItemSaat =new QTableWidgetItem();
        newItemGorev->setText(text);
        newItemSaat -> setText(n.toString());
        //newItem..setText(text);
        //newItem.se(n);
        //model->setStringList(list);
        ui->tableWidget->insertRow(item_count);
        ui->tableWidget->setItem(item_count,0,newItemGorev);
        ui->tableWidget->setItem(item_count,1,newItemSaat);

        item_count++;
        ui->tableWidget->setRowCount(item_count);
        ui->jobEntrytxt->setText("");
        timer.stop();



        //QString my_formatted_string1 = QString("Başlık:%7   Süre:%4%1:%5%2:%6%3").arg(QString::number(saat), QString::number(dakika), QString::number(saniye),place4,place5,place6,text);
        saat=  0;
        dakika=0;
        saniye=0;
        pause=true;
        running=false;
        if(saat<10)
            place4="0";
        else
            place4="";
        if(dakika<10)
            place5="0";
        else
            place5="";
        if(saniye<10)
            place6="0";
        else
            place6="";

        QString my_formatted_string = QString("%4%1:%5%2:%6%3").arg(QString::number(saat), QString::number(dakika), QString::number(saniye),place4,place5,place6);
        ui->lcdPanel->display(my_formatted_string);
        ui->stopButton->setEnabled(false);

    }
    else
    {
        ui->labelWarning->setText("Type your work title...");
    }


    ui->stopButton->setEnabled(false);
    ui->stopButton->setText("Stop/Continue");
    ui->startButton->setEnabled(true);
    ui->tableWidget->setEnabled(true);

}


//void MainWindow::on_gorevlerListWidget_itemDoubleClicked(QListWidgetItem *item)
//{
//    item->~QListWidgetItem();
//}

void MainWindow::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    if(item->column()==0)
    {
        QTime deneme=  map[item->text()];
        saat=deneme.hour();
        dakika=deneme.minute();
        saniye=deneme.second();
        if(saat<10)
            place4="0";
        else
            place4="";
        if(dakika<10)
            place5="0";
        else
            place5="";
        if(saniye<10)
            place6="0";
        else
            place6="";

        QString my_formatted_string = QString("%4%1:%5%2:%6%3").arg(QString::number(saat), QString::number(dakika), QString::number(saniye),place4,place5,place6);

        ui->jobEntrytxt->setText(item->text());
        map.remove(item->text());
        ui->tableWidget->removeRow(item->row());
        ui->lcdPanel->display(my_formatted_string);
        item_count--;
        //running=true;
        ui->stopButton->setText("Stop/Continue");
        ui->stopButton->setEnabled(false);
        ui->startButton->setEnabled(true);

        ui->tableWidget->setEnabled(false);

    }
}
