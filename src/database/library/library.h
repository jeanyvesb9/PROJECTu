#ifndef LIBRARY_H
#define LIBRARY_H

#include <QObject>
#include <QtGlobal>
#include <QSharedPointer>
#include <QHash>
#include "src/database/song.h"
#include "src/database/album.h"
#include "src/database/playlist.h"
#include "src/database/artist.h"
#include "src/database/item_id.h"

namespace Database
{

class Library : public QObject
{
    Q_OBJECT
public:
    explicit Library(QObject *parent = 0);
    ~Library();

    enum State {
        Ordered, BeginInserting, InsertingOrdered, InsertingDisordered
    };

    void setSongList(QHash<quint64, QSharedPointer<Database::Song>> songList, QList<quint64> orderedList);
    const QHash<quint64, QSharedPointer<Database::Song>> *getSongList() const { return &songList; }
    const QList<quint64> *getOrderedSongList() const { return &orderedSongList; }

    void setAlbumList(QHash<quint64, QSharedPointer<Database::Album>> albumList, QList<quint64> orderedList);
    const QHash<quint64, QSharedPointer<Database::Album>> *getAlbumList() const { return &albumList; }
    const QList<quint64> *getOrderedAlbumList() const { return &orderedAlbumList; }

    void setPlaylistList(QHash<quint32, QSharedPointer<Database::Playlist>> playlistList, QList<quint32> orderedList);
    const QHash<quint32, QSharedPointer<Database::Playlist>> *getPlaylistList() const { return &playlistList; }
    const QList<quint32> *getOrderedPlaylistList() const { return &orderedPlaylistList; }

    void setArtistList(QHash<quint64, QSharedPointer<Database::Artist>> artistList, QList<quint64> orderedList);
    const QHash<quint64, QSharedPointer<Database::Artist>> *getArtistList() const { return &artistList; }
    const QList<quint64> *getOrderedArtistList() const { return &orderedArtistList; }

    void beginInserting();
    void endInserting();

    void addSong(QSharedPointer<Database::Song> song, bool order = 1);
    void addAlbum(QSharedPointer<Database::Album> album, bool order = 1);
    void addPlaylist(QSharedPointer<Database::Playlist> playlist, bool order = 1);
    void addArtist(QSharedPointer<Database::Artist> artist, bool order = 1);

    void removeSong(quint64 id, qint64 place = -1);
    void removeAlbum(quint64 id, qint64 place = -1);
    void removePlaylist(quint32 id, qint64 place = -1);
    void removeArtist(quint64 id, qint64 place = -1);

    QWeakPointer<Song> getSong(quint64 songId) { return songList.value(songId).toWeakRef(); }
    quint64 getSongAtPlace(quint32 place) const { return orderedSongList.at(place); }
    QWeakPointer<Album> getAlbum(quint64 albumId) { return albumList.value(albumId).toWeakRef(); }
    quint64 getAlbumAtPlace(quint32 place) const { return orderedAlbumList.at(place); }
    QWeakPointer<Playlist> getPlaylist(quint32 playlistId) { return playlistList.value(playlistId).toWeakRef(); }
    quint64 getPlaylistAtPlace(quint32 place) const { return orderedPlaylistList.at(place); }
    QWeakPointer<Artist> getArtist(quint64 artistId) { return artistList.value(artistId).toWeakRef(); }
    quint64 getArtistAtPlace(quint32 place) const { return orderedArtistList.at(place); }

private:
    QHash<quint64, QSharedPointer<Database::Song>> songList;
    QList<quint64> orderedSongList;
    QHash<quint64, QSharedPointer<Database::Album>> albumList;
    QList<quint64> orderedAlbumList;
    QHash<quint32, QSharedPointer<Database::Playlist>> playlistList;
    QList<quint32> orderedPlaylistList;
    QHash<quint64, QSharedPointer<Database::Artist>> artistList;
    QList<quint64> orderedArtistList;

    State state;
    bool songsOrdered;
    bool albumsOrdered;
    bool playlistsOrdered;
    bool artistsOrdered;

    bool songsEdited;
    bool albumsEdited;
    bool playlistsEdited;
    bool artistsEdited;

    void order();

signals:
    void updated();
    void updatedSongs();
    void updatedAlbums();
    void updatedPlaylists();
    void updatedArtists();

public slots:

};

namespace Functors
{

class SongLessThan
{
public:
    SongLessThan(Library *library);
    bool operator()(quint64 a, quint64 b);
private:
    Library *lib;
};

class AlbumLessThan
{
public:
    AlbumLessThan(Library *library);
    bool operator()(quint64 a, quint64 b);
private:
    Library *lib;
};
class PlaylistLessThan
{
public:
    PlaylistLessThan(Library *library);
    bool operator()(quint64 a, quint64 b);
private:
    Library *lib;
};
class ArtistLessThan
{
public:
    ArtistLessThan(Library *library);
    bool operator()(quint64 a, quint64 b);
private:
    Library *lib;
};

}

}
#endif // LIBRARY_H
