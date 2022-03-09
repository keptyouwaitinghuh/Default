#include "info.h"


Info::Info(QString pr, QString tsk, QString ex, QString head, QDate rD, QDate dl, QDate d)
{
    project=pr;
    task=tsk;
    exec=ex;
    header=head;
    returnDate=rD;
    deadline=dl;
    date=d;
}
