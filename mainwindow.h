#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QFile>
#include "plist.h"
#include "plist.cpp"
#include "info.h"
#include <iostream>
#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; class CreateWindow;}
QT_END_NAMESPACE




class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void readAllData();
    void writeAllData();
    bool readData(Info &tmp);
    void writeData(Info &data);

    void listToCombo();

    void showData(Info &data);
    void clearText();

    friend class CreateWindow;

private slots:
    void on_addButton_clicked();


    void on_deleteButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_editButton_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_searchButton_clicked();

    void on_listButton_clicked();

    void on_openButton_clicked();

private:
    Ui::MainWindow *ui;
    PList<Info> list;
    QTextStream stream;
    QFile file;
    bool error;
    QVector<int> searchResults;
};




#endif // MAINWINDOW_H
