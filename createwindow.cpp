#include "createwindow.h"
#include "ui_createwindow.h"
#include "ui_mainwindow.h"

CreateWindow::CreateWindow(MainWindow &wc, CreateWindowMode mode,QWidget *parent)
    : QWidget{parent}, w(wc), ui(new Ui::CreateWindow), mode(mode)
{
    ui->setupUi(this);
    if(mode == EDIT)
    {
        Info data = w.list[w.ui->comboBox->currentIndex()]->data;
        ui->projectField->setText(data.project);
        ui->taskField->setText(data.task);
        ui->execField->setText(data.exec);
        ui->headerField->setText(data.header);
        ui->dateField->setDate(data.date);
        ui->deadLineField->setDate(data.deadline);
        ui->returnDateField->setDate(data.returnDate);
        ui->pushButton->setText("Редактировать");
    }
    else if(mode == ADD)
    {
        ui->projectField->clear();
        ui->taskField->clear();
        ui->execField->clear();
        ui->headerField->clear();
        ui->dateField->clear();
        ui->deadLineField->clear();
        ui->returnDateField->clear();
        ui->pushButton->setText("Добавить");
    }
    else if(mode == SEARCH)
    {
        ui->projectField->clear();
        ui->taskField->clear();
        ui->execField->clear();
        ui->headerField->clear();
        ui->dateField->clear();
        ui->deadLineField->clear();
        ui->returnDateField->clear();
        ui->pushButton->setText("Поиск");
    }
}
void CreateWindow::on_cancelButton_clicked()
{
    close();
}

bool CreateWindow::everythingDefined()
{
    bool value = true;
    value=value && ui->taskField->text()!="\0";
    value=value && ui->execField->text()!="\0";
    value=value && ui->headerField->text()!="\0";
    value=value && ui->projectField->text()!="\0";

    return value;
}

void CreateWindow::on_pushButton_clicked()
{
        std::cout<<"pushbutton\n";
        Info *tmp=new Info;

        tmp->project = ui->projectField->text();
        tmp->exec = ui->execField->text();
        tmp->header = ui->headerField->text();
        tmp->task = ui->taskField->text();
        tmp->date = ui->dateField->date();
        tmp->deadline = ui->deadLineField->date();
        tmp->returnDate = ui->returnDateField->date();
        if(mode == ADD && everythingDefined())
        {
            w.list.push_back(tmp);
            w.listToCombo();
        }
        else if(mode == EDIT && everythingDefined())
        {
            int i=w.ui->comboBox->currentIndex();
            w.list[i]->data=*tmp;
            w.listToCombo();
            w.ui->comboBox->setCurrentIndex(i);
        }
        else if(mode == SEARCH)
        {
            search(tmp);
        }

        close();
}

bool CreateWindow::check(Info dataIn, Info dataReal)
{
    bool retValue = true;

    retValue = retValue && (dataIn.date.toString() =="01.01.2000"  || dataIn.date == dataReal.date );
    retValue = retValue && (dataIn.deadline.toString() =="01.01.2000"  ||dataIn.deadline == dataReal.deadline);
    retValue = retValue && (dataIn.returnDate.toString() =="01.01.2000"  ||dataIn.returnDate == dataReal.returnDate);

    retValue = retValue && (dataIn.exec == "\0" || dataIn.exec == dataReal.exec);
    retValue = retValue && (dataIn.header == "\0" || dataIn.header == dataReal.header);
    retValue = retValue && (dataIn.project == "\0" || dataIn.project == dataReal.project);
    retValue = retValue && (dataIn.task == "\0" || dataIn.task == dataReal.task);

    return retValue;
}

void CreateWindow::search(Info *tmp)
{
    w.ui->listWidget->clear();
    w.searchResults.clear();
    Nod<Info> *ptr = w.list.getFirst();
    int i=0;
    while(ptr != nullptr)
    {
        if(check(*tmp,ptr->data))
        {
            w.ui->listWidget->addItem(ptr->data.exec);
            w.searchResults.append(i);
        }
        ++i;
        ptr=ptr->next;
    }
}
