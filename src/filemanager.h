#ifndef FILETRACKER_H
#define FILETRACKER_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QThread>
#include <QUrl>
#include <QDir>
#include <QFile>
#include <QMutex>
#include <QMutexLocker>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/mp4file.h>
#include <taglib/id3v2tag.h>
#include <taglib/mpegfile.h>

namespace BackEnd {

class FileTracker : public QObject
{
    Q_OBJECT

public:
    explicit FileTracker(QObject *parent = 0);
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

    bool parseDir(QString url);
    bool parseFile(QString url);

signals:
    void private_finished();

public slots:
    void setSearchDirectory(const QString &value);
    void setFileFormats(const QStringList &value);
    void setRecursive(bool value);
    void setCheckDB(bool value);

    void private_startSearch();
};

}

#endif // FILETRACKER_H
