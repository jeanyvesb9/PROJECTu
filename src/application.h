#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include "src/database/database.h"

class Application : public QObject
{
    Q_OBJECT
public:
    explicit Application(QObject *parent = 0);

private:
    Database db;

signals:

public slots:

private slots:


};

#endif // APPLICATION_H
