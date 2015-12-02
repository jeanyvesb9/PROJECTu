#ifndef SONGFILE_H
#define SONGFILE_H

#include <QObject>

class SongFile : public QObject
{
    Q_OBJECT
public:
    explicit SongFile(QObject *parent = 0);

signals:

public slots:
};

#endif // SONGFILE_H
