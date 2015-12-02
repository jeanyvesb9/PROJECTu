#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QThread>
#include <QUrl>
#include <QDir>
#include <QFile>
#include <QMutex>
#include <QMutexLocker>
#include <QPointer>
#include <QSharedPointer>
#include <QSqlDatabase>
//#include <cstring>
//#include <taglib/fileref.h>
//#include <taglib/tag.h>
//#include <taglib/mp4file.h>
//#include <taglib/id3v2tag.h>
//#include <taglib/mpegfile.h>
#include "src/database/library/library.h"
#include "src/database/songfile.h"

namespace BackEnd {

struct SongExtraMetadata {
    uint year;
    QByteArray album;
    QByteArray albumArtist;
    QByteArray artist;
    QByteArray genre;
};

class FileManager : public QObject
{
    Q_OBJECT

public:
    explicit FileManager(QObject *parent = 0);
    QString getSearchDirectory() const;
    QStringList getFileFormats() const;
    bool getRecursive() const;
    bool getCheckDB() const;

private:
    QMutex mutex;
    QString searchDirectory;
    QStringList fileFormats;
    bool recursive;
    bool checkDB;

    QSqlDatabase db;

    bool parseDir(QString url);
    QSharedPointer<DB::Song> parseFile(QString url, SongExtraMetadata *meta);

signals:
    void private_finished();

public slots:
    void setSearchDirectory(const QString &value);
    void setFileFormats(const QStringList &value);
    void setRecursive(bool value);
    void setCheckDB(bool value);
    void setDB(QString url);

    void private_startSearch();
};

}

#endif // FILEMANAGER_H
