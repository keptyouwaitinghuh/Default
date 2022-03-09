#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createwindow.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    file.setFileName("file.data");
    file.open(QIODevice::ReadWrite);
    stream.setDevice(&file);
    readAllData();
    listToCombo();
}

void MainWindow::readData(Info &tmp)
{

    stream >> tmp.date;
    stream >> tmp.deadline;
    stream >> tmp.exec;
    stream >> tmp.header;
    stream >> tmp.project;
    stream >> tmp.returnDate;
    stream >> tmp.task;

}

void MainWindow::readAllData()
{
    while(!file.atEnd())
    {
        std::cout<<"read\n";
        Info tmp;
        readData(tmp);
        list.push_back(&tmp);
    }
}

void MainWindow::writeData(Info &tmp)
{
    stream << tmp.date;
    stream << tmp.deadline;
    stream << tmp.exec;
    stream << tmp.header;
    stream << tmp.project;
    stream << tmp.returnDate;
    stream << tmp.task;

}

void MainWindow::writeAllData()
{
    file.close();
    file.open(QIODevice::ReadWrite | QIODevice::Truncate);
    Nod<Info> *ptr=list.getFirst();
    while(ptr != nullptr)
    {
        std::cout << "write";
        writeData(ptr->data);
        ptr = ptr->next;
    }
}

MainWindow::~MainWindow()
{
    writeAllData();
    delete ui;
}

void MainWindow::listToCombo()
{
    ui->comboBox->clear();
    Nod<Info> *ptr=list.getFirst();
    int i=0;
    while(ptr != nullptr)
    {
        qDebug()<<"listToCombo" << i <<'\n';
        ui->comboBox->addItem(ptr->data.exec);
        qDebug()<<"listToCombo" << i << ptr->data.exec;
        ptr=ptr->next;
        i++;
    }
}

void MainWindow::showData(Info &data)
{
    qDebug() << "showData in";
    ui->projectField->setText(data.project);
    qDebug()<< data.exec;
    ui->taskField->setText(data.task);
    ui->execField->setText(data.exec);
    ui->headerField->setText(data.header);
    ui->dateField->setText(data.date.toString("dd.MM.yyyy"));
    ui->deadLineField->setText(data.deadline.toString("dd.MM.yyyy"));
    ui->returnDateField->setText(data.returnDate.toString("dd.MM.yyyy"));
    qDebug() <<"showData out 1";
}

void MainWindow::clearText()
{
    ui->projectField->clear();
    ui->taskField->clear();
    ui->execField->clear();
    ui->headerField->clear();
    ui->dateField->clear();
    ui->deadLineField->clear();
    ui->returnDateField->clear();
}

void MainWindow::on_addButton_clicked()
{
    qDebug()<<"addButton\n";
   static CreateWindow cw(*this, ADD);
   cw.show();
}

void MainWindow::on_deleteButton_clicked()
{
    qDebug() << "delete button clicked";
    int g= ui->comboBox->currentIndex();
    qDebug() << g;
    ui->comboBox->removeItem(g);
    list.remove(list[g]);
    listToCombo();
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if(list.getFirst() != nullptr && ui->comboBox->currentIndex() != -1)
        showData(list[index]->data);

    else
        clearText();
}

void MainWindow::on_editButton_clicked()
{
    static CreateWindow cw(*this, EDIT);
    cw.show();
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    int i=ui->listWidget->currentRow();
    ui->comboBox->setCurrentIndex(searchResults[i]);
}


void MainWindow::on_searchButton_clicked()
{
    static CreateWindow cw(*this, SEARCH);
    cw.show();
}


void MainWindow::on_listButton_clicked()
{
    ui->listWidget->clear();
    searchResults.clear();
    Nod<Info> *ptr = list.getFirst();
    int i=0;
    while(ptr != nullptr)
    {
        if(ptr->data.deadline < ptr->data.returnDate)
        {
            ui->listWidget->addItem(ptr->data.exec);
            searchResults.append(i);
        }
        ++i;
        ptr=ptr->next;
    }
}

