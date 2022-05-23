#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createwindow.h"
#include <QFileDialog>
#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , error(false)
{
    ui->setupUi(this);
    QString path=QFileDialog::getOpenFileName(this, "Выберите файл",
                                              "D:\\Task1_4",
                                              "(*.txt)");
    file.setFileName(path);
    file.open(QIODevice::ReadWrite);
    stream.setDevice(&file);

    readAllData();
    listToCombo();
}

bool MainWindow::readData(Info &tmp)
{
    bool r = 1;
    QString str;

    str = stream.readLine();
    qDebug() << str;
    tmp.date = QDate::fromString(str, "dd.MM.yyyy");
    r = r && tmp.date.isValid();
    qDebug() << r;

    str = stream.readLine();
    qDebug() << str;
    tmp.deadline = QDate::fromString(str, "dd.MM.yyyy");
    r = r && tmp.deadline.isValid();

    tmp.exec = stream.readLine();
    tmp.header = stream.readLine();
    tmp.project = stream.readLine();

    str = stream.readLine();
    qDebug() << str;
    tmp.returnDate = QDate::fromString(str, "dd.MM.yyyy");
    r = r && tmp.returnDate.isValid();

    tmp.task = stream.readLine();

    return r;
}

void MainWindow::readAllData()
{
    int N=0;

    while(!stream.atEnd())
    {
        qDebug() << stream.readLine();
        ++N;
    }

    qDebug() << N;
    N = N/7;

    list.clear();

    stream.seek(0);

    while(N)
    {
        Info tmp;
        bool c = readData(tmp);
        if(!c)
        {
            QMessageBox::critical(this, "заебал", "Файл некорректен");
            error = 1;
            break;
        }
        list.push_back(&tmp);
        --N;
    }
}

void MainWindow::writeData(Info &tmp)
{
    stream << tmp.date.toString("dd.MM.yyyy") << '\n';
    stream << tmp.deadline.toString("dd.MM.yyyy") << '\n';
    stream << tmp.exec << '\n';
    stream << tmp.header << '\n';
    stream << tmp.project << '\n';
    stream << tmp.returnDate.toString("dd.MM.yyyy") << '\n';
    stream << tmp.task << '\n';
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
    if(error) return;
    ui->comboBox->clear();
    qDebug() <<"очистили";
    Nod<Info> *ptr=list.getFirst();
    qDebug() << "присвоили";
    int i=0;
    while(ptr != nullptr)
    {
        qDebug() << "зашли в запись в комбо";
        ui->comboBox->addItem(ptr->data.exec);
        ptr=ptr->next;
        i++;
    }
    qDebug() << "Выход из листТо комбо";
}

void MainWindow::showData(Info &data)
{
    if(error) return;
    ui->projectField->setText(data.project);
    ui->taskField->setText(data.task);
    ui->execField->setText(data.exec);
    ui->headerField->setText(data.header);
    ui->dateField->setText(data.date.toString("dd.MM.yyyy"));
    ui->deadLineField->setText(data.deadline.toString("dd.MM.yyyy"));
    ui->returnDateField->setText(data.returnDate.toString("dd.MM.yyyy"));
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
   if(error) return;
   static CreateWindow cw(*this, ADD);
   cw.show();
}

void MainWindow::on_deleteButton_clicked()
{
    if(error) return;
    int g= ui->comboBox->currentIndex();
    ui->comboBox->removeItem(g);
    list.remove(list[g]);
    listToCombo();
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if(error) return;
    if(list.getFirst() != nullptr && ui->comboBox->currentIndex() != -1)
        showData(list[index]->data);

    else
        clearText();
}

void MainWindow::on_editButton_clicked()
{
    if(error) return;
    if(list.is_empty()) return;
    static CreateWindow cw(*this, EDIT);
    cw.show();
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    if(error) return;
    int i=ui->listWidget->currentRow();
    ui->comboBox->setCurrentIndex(searchResults[i]);
}


void MainWindow::on_searchButton_clicked()
{
    if(error) return;
    static CreateWindow cw(*this, SEARCH);
    cw.show();
}


void MainWindow::on_listButton_clicked()
{
    if(error) return;
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


void MainWindow::on_openButton_clicked()
{
    qDebug() << "---------------------------------\nis error " << error;
    if(!error) writeAllData();
    clearText();
    list.clear();
    ui->comboBox->clear();
    error = false;
    QString toFile = QFileDialog::getOpenFileName(this, "Выберите файл",
                                                      "D:\\Task1_4",
                                                      "(*.txt)");
    file.close();
    file.setFileName(toFile);
    stream.setDevice(&file);
    file.open(QIODevice::ReadWrite);
    readAllData();
    listToCombo();
}

