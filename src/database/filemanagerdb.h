#ifndef FILEMANAGERDB_H
#define FILEMANAGERDB_H

#include <QObject>
#include <QString>
#include <QSqlDatabase>

class FileManagerDB : public QObject
{
    Q_OBJECT
public:
    explicit FileManagerDB(QObject *parent = 0);

    QString getDBFile() const;
    bool setDBFile(const QString &value);
    bool connectDatabase();
    bool closeDatabase();

private:
    QString DBfile;
    QSqlDatabase db;

};

#endif // FILEMANAGERDB_H
