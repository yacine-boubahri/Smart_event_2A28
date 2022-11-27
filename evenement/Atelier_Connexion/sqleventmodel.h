#ifndef SQLEVENTMODEL_H
#define SQLEVENTMODEL_H
#include <QList>
#include <QObject>
#include "evenement.h"


class sqleventmodel
{
public:
    sqleventmodel();
      Q_INVOKABLE QList<QObject*> eventsForDate(const QDate &date);
};

#endif // SQLEVENTMODEL_H
