#include "src/database/library/playlist.h"

using namespace DB;

Playlist::Playlist(QObject *parent)
    :QObject(parent)
{

}

Playlist::Playlist(quint32 id, QString name, QObject *parent)
    :QObject(parent), id{id}, name{name.toUtf8()}
{

}

Playlist::~Playlist()
{
    emit playlistDeleted(this);
}

void Playlist::setId(quint32 id)
{
    this->id = id;
}

void Playlist::setName(QString name)
{
    this->name = name.toUtf8();
}

void Playlist::setName(QByteArray name)
{
    this->name = name;
}

void Playlist::setSongList(QList<quint64> songs)
{
    this->songList = songs;
}

void Playlist::addSong(qint16 possition, quint64 song)
{
    this->songList.insert(possition, song);
}

void Playlist::removeSong(qint16 possition)
{
    return this->songList.removeAt(possition);
}

void Playlist::moveSong(qint16 from, qint16 to)
{
    this->songList.move(from, to);
}
