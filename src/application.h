#ifndef APPLLICATION_H
#define APPLLICATION_H

#include <QObject>

class Appllication : public QObject
{
    Q_OBJECT
public:
    explicit Appllication(QObject *parent = 0);

signals:

public slots:
};

#endif // APPLLICATION_H
