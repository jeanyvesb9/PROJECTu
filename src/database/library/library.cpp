#include "src/database/library.h"

using namespace Database;

Library::Library(QObject *parent)
    : QObject(parent), state{State::Ordered}, songsOrdered{1}, albumsOrdered{1},
      playlistsOrdered{1}, artistsOrdered{1}, songsEdited{0}, albumsEdited{0},
      playlistsEdited{0}, artistsEdited{0}
{

}

Library::~Library()
{

}

void Library::setSongList(QHash<quint64, QSharedPointer<Song>> songList, QList<quint64> orderedList)
{
    this->songList = songList;
    this->orderedSongList = orderedList;
}

void Library::setAlbumList(QHash<quint64, QSharedPointer<Album>> albumList, QList<quint64> orderedList)
{
    this->albumList = albumList;
    this->orderedAlbumList = orderedList;
}

void Library::setPlaylistList(QHash<quint32, QSharedPointer<Playlist> > playlistList, QList<quint32> orderedList)
{
    this->playlistList = playlistList;
    this->orderedPlaylistList = orderedList;
}

void Library::setArtistList(QHash<quint64, QSharedPointer<Artist>> artistList, QList<quint64> orderedList)
{
    this->artistList = artistList;
    this->orderedArtistList = orderedList;
}

void Library::beginInserting()
{
    if(this->state == State::Ordered)
    {
        this->state = State::BeginInserting;
    }
}

void Library::endInserting()
{
    if(this->state == State::Ordered || this->state == State::BeginInserting)
        return;
    else if(this->state == State::InsertingDisordered)
        this->order();
    this->state = State::Ordered;

    if(songsEdited)
        emit updatedSongs();
    if(albumsEdited)
        emit updatedAlbums();
    if(playlistsEdited)
        emit updatedPlaylists();
    if(artistsEdited)
        emit updatedArtists();
    songsEdited =0;

    emit updated();
}

void Library::addSong(QSharedPointer<Song> song, bool order)
{
    beginInserting();
    this->songList.insert(song->getId(), song);
    if(order)
    {
        if(this->state == State::BeginInserting || this->state == State::InsertingDisordered)
        {
            this->state = State::InsertingOrdered;
        }
    }
    else
    {
        if(this->state == State::BeginInserting || this->state == State::InsertingOrdered)
        {
            this->state = State::InsertingDisordered;
        }
    }
    this->orderedSongList.append(song->getId());
    songsEdited = 1;
    songsOrdered = 0;
    if(order)
    {
        if(this->state == State::BeginInserting)
        {
            this->state = State::InsertingOrdered;
        }
        endInserting();
        return;
    }
}

void Library::addAlbum(QSharedPointer<Album> album, bool order)
{
    beginInserting();
    this->albumList.insert(album->getId(), album);
    if(order)
    {
        if(this->state == State::BeginInserting || this->state == State::InsertingDisordered)
        {
            this->state = State::InsertingOrdered;
        }
    }
    else
    {
        if(this->state == State::BeginInserting || this->state == State::InsertingOrdered)
        {
            this->state = State::InsertingDisordered;
        }
    }
    this->orderedAlbumList.append(album->getId());
    albumsEdited = 1;
    albumsOrdered = 0;
    if(order)
    {
        if(this->state == State::BeginInserting)
        {
            this->state = State::InsertingOrdered;
        }
        endInserting();
        return;
    }
}

void Library::addPlaylist(QSharedPointer<Playlist> playlist, bool order)
{
    beginInserting();
    this->playlistList.insert(playlist->getId(), playlist);
    if(order)
    {
        if(this->state == State::BeginInserting || this->state == State::InsertingDisordered)
        {
            this->state = State::InsertingOrdered;
        }
    }
    else
    {
        if(this->state == State::BeginInserting || this->state == State::InsertingOrdered)
        {
            this->state = State::InsertingDisordered;
        }
    }
    this->orderedPlaylistList.append(playlist->getId());
    playlistsEdited = 1;
    playlistsOrdered = 0;
    if(order)
    {
        if(this->state == State::BeginInserting)
        {
            this->state = State::InsertingOrdered;
        }
        endInserting();
        return;
    }
}

void Library::addArtist(QSharedPointer<Artist> artist, bool order)
{
    beginInserting();
    this->artistList.insert(artist->getId(), artist);
    if(order)
    {
        if(this->state == State::BeginInserting || this->state == State::InsertingDisordered)
        {
            this->state = State::InsertingOrdered;
        }
    }
    else
    {
        if(this->state == State::BeginInserting || this->state == State::InsertingOrdered)
        {
            this->state = State::InsertingDisordered;
        }
    }
    this->orderedArtistList.append(artist->getId());
    artistsEdited = 1;
    artistsOrdered = 0;
    if(order)
    {
        if(this->state == State::BeginInserting)
        {
            this->state = State::InsertingOrdered;
        }
        endInserting();
        return;
    }
}

void Library::removeSong(quint64 id, qint64 place)
{
    this->songList.remove(id);
    if(place == -1)
    {
        for(int i = 0; i < orderedSongList.size(); i++)
        {
            if(orderedSongList.at(i) == id)
            {
                orderedSongList.removeAt(i);
                break;
            }
        }
    }
    else
    {
        orderedSongList.removeAt(place);
    }
}

void Library::removeAlbum(quint64 id, qint64 place)
{
    this->albumList.remove(id);
    if(place == -1)
    {
        for(int i = 0; i < orderedAlbumList.size(); i++)
        {
            if(orderedAlbumList.at(i) == id)
            {
                orderedAlbumList.removeAt(i);
                break;
            }
        }
    }
    else
    {
        orderedAlbumList.removeAt(place);
    }
}

void Library::removePlaylist(quint32 id, qint64 place)
{
    this->playlistList.remove(id);
    if(place == -1)
    {
        for(int i = 0; i < orderedPlaylistList.size(); i++)
        {
            if(orderedPlaylistList.at(i) == id)
            {
                orderedPlaylistList.removeAt(i);
                break;
            }
        }
    }
    else
    {
        orderedPlaylistList.removeAt(place);
    }
}

void Library::removeArtist(quint64 id, qint64 place)
{
    this->artistList.remove(id);
    if(place == -1)
    {
        for(int i = 0; i < orderedArtistList.size(); i++)
        {
            if(orderedArtistList.at(i) == id)
            {
                orderedArtistList.removeAt(i);
                break;
            }
        }
    }
    else
    {
        orderedArtistList.removeAt(place);
    }
}

void Library::order()
{
    if(!this->songsOrdered)
    {
        Functors::SongLessThan sortFunctor(this);
        qStableSort(orderedSongList.begin(), orderedSongList.end(), sortFunctor);
        songsOrdered = 1;
    }
    if(!this->albumsOrdered)
    {
        Functors::AlbumLessThan sortFunctor(this);
        qStableSort(orderedAlbumList.begin(), orderedAlbumList.end(), sortFunctor);
        albumsOrdered = 1;
    }
    if(!this->playlistsOrdered)
    {
        Functors::PlaylistLessThan sortFunctor(this);
        qStableSort(orderedPlaylistList.begin(), orderedPlaylistList.end(), sortFunctor);
        playlistsOrdered = 1;
    }
    if(!this->artistsOrdered)
    {
        Functors::ArtistLessThan sortFunctor(this);
        qStableSort(orderedArtistList.begin(), orderedArtistList.end(), sortFunctor);
        artistsOrdered = 1;
    }
}


Functors::SongLessThan::SongLessThan(Library *library)
    :lib{library}
{

}

bool Functors::SongLessThan::operator()(quint64 a, quint64 b)
{
    auto aPtr = lib->getSong(a).lock();
    auto bPtr = lib->getSong(b).lock();

    int cmp = QString::compare(aPtr->getName(), bPtr->getName(), Qt::CaseInsensitive);
    if(cmp < 0)
        return true;
    return false;
}

Functors::AlbumLessThan::AlbumLessThan(Library *library)
    :lib{library}
{

}

bool Functors::AlbumLessThan::operator()(quint64 a, quint64 b)
{
    auto aPtr = lib->getAlbum(a).lock();
    auto bPtr = lib->getAlbum(b).lock();

    int cmp = QString::compare(aPtr->getName(), bPtr->getName(), Qt::CaseInsensitive);
    if(cmp < 0)
        return true;
    return false;
}

Functors::PlaylistLessThan::PlaylistLessThan(Library *library)
    :lib{library}
{

}

bool Functors::PlaylistLessThan::operator()(quint64 a, quint64 b)
{
    auto aPtr = lib->getPlaylist(a).lock();
    auto bPtr = lib->getPlaylist(b).lock();

    int cmp = QString::compare(aPtr->getName(), bPtr->getName(), Qt::CaseInsensitive);
    if(cmp < 0)
        return true;
    return false;
}

Functors::ArtistLessThan::ArtistLessThan(Library *library)
    :lib{library}
{

}

bool Functors::ArtistLessThan::operator()(quint64 a, quint64 b)
{
    auto aPtr = lib->getArtist(a).lock();
    auto bPtr = lib->getArtist(b).lock();

    int cmp = QString::compare(aPtr->getName(), bPtr->getName(), Qt::CaseInsensitive);
    if(cmp < 0)
        return true;
    return false;
}
