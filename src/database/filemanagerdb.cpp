#include "filemanagerdb.h"

FileManagerDB::FileManagerDB(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}
QString FileManagerDB::getDBFile() const
{
    return DBfile;
}

bool FileManagerDB::setDBFile(const QString &value)
{
    if(db.isOpen())
    {
        return false;
    }
    DBfile = value;
}

bool FileManagerDB::connectDatabase()
{
    if(db.isOpen())
        db.close();
    db.setDatabaseName(DBfile);
    return db.open();
}

bool FileManagerDB::closeDatabase()
{
    if(db.isOpen())
    {
        db.close();
        return true;
    }
    return false;
}
