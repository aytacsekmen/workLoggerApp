#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include<QStringListModel>
#include<QDateTime>
#include<QListWidgetItem>
#include<QTableWidgetItem>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void showTimes();

    void on_startButton_clicked();

    void on_stopButton_clicked();

    void on_resetButton_clicked();

    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);

private:
    int saat=  0;
    int dakika=0;
    int saniye=0;
    bool pause;
    bool running;
    bool entry_control;
    int item_count=0;
    QString place4;
    QString place5;
    QString place6;
    Ui::MainWindow *ui;
    QTimer timer;
    QStringListModel *model;
    QMap<QString,QTime> map;
};
#endif // MAINWINDOW_H
