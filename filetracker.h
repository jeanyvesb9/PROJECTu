#ifndef FILETRACKER_H
#define FILETRACKER_H

#include <QObject>

class FileTracker : public QObject
{
    Q_OBJECT
public:
    explicit FileTracker(QObject *parent = 0);

signals:

public slots:
};

#endif // FILETRACKER_H
