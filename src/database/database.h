#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QThread>
#include "src/database/library/library.h"
#include "src/database/filemanager.h"

namespace BackEnd {
    enum class needUpdate { NoUpdate = 0, Songs, SongsAlbums, SongsAlbumsArtists};
}

class Database : public QObject
{
    Q_OBJECT
public:
    Database(QObject *parent = 0);
    ~Database();

private:
    QSharedPointer<DB::Library> library;
    QSharedPointer<DB::Library> externalLibrary;
    QThread *fileManagerThread;
    BackEnd::FileManager *fileManager;


    bool scanningFiles;
    bool scanningExternal;
    bool internalScanQueue;
    bool externalScanQueue;

signals:
    void songsFullUpdate();
    void albumsFullUpdate();
    void artistsFullUpdate();

public slots:
    void performScan(QString dir, bool recursive); //Will emit songsFull
    void performExternalScan(QString dir, bool recursive); //Will emit externalParseFinshed();

    void deleteSong(quint64 id);
    void hideSong(quint64 id);
    void unhideSong(quint64 id);
    void deleteAlbum(quint64 id);
    void deleteArtist(quint64 id);

private slots:
    void fileManagerFinished();

};

#endif // DATABASE_H
