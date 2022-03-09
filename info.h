#ifndef INFO_H
#define INFO_H

#include <QString>
#include <QDate>
#include <QtCore>
struct Info
{
public:
    QString project;
    QString task;
    QString exec;
    QString header;
    QDate returnDate, deadline, date;


    Info(QString pr, QString tsk, QString ex, QString head,QDate rD, QDate dl, QDate d );
    Info () {};
};

#endif // INFO_H
