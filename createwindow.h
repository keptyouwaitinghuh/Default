#ifndef CREATEWINDOW_H
#define CREATEWINDOW_H

#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CreateWindow;}
QT_END_NAMESPACE

enum CreateWindowMode
{
    ADD,
    EDIT,
    SEARCH
};

class CreateWindow : public QWidget
{
    Q_OBJECT

    MainWindow &w;
    CreateWindowMode mode;
    Ui::CreateWindow *ui;

    bool everythingDefined();
    bool check(Info data1, Info data2);
    void search(Info *data);

public:
    CreateWindow(MainWindow &w,CreateWindowMode mode, QWidget *parent = nullptr);

private slots:
    void on_pushButton_clicked();

    void on_cancelButton_clicked();
};
#endif // CREATEWINDOW_H
