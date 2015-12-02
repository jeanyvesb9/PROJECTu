#include "src/database/song.h"

using namespace Database;

Song::Song(QObject *parent)
    :QObject(parent)
{

}

Song::Song(quint64 id, QByteArray name, QByteArray file, quint32 time, quint16 trackNumber, quint16 discNumber,
           quint64 album, quint64 artist, QObject *parent)
    : QObject(parent), id{id}, name{name}, file{file}, time{time}, trackNumber{trackNumber},
      discNumber{discNumber}, album{album}, artist{artist}
{

}

Song::~Song()
{

}

void Song::setId(quint64 id)
{
    this->id = id;
}

void Song::setName(QString name)
{
    this->name = name.toUtf8();
}

void Song::setName(QByteArray name)
{
    this->name = name;
}

void Song::setAlbum(quint64 album)
{
    this->album = album;
}

void Song::setTime(quint32 time)
{
    this->time = time;
}

void Song::setTrackNumber(quint16 trackNumber)
{
    this->trackNumber = trackNumber;
}

void Song::setDiscNumber(quint16 discNumber)
{
    this->discNumber = discNumber;
}

void Song::setArtist(quint64 artist)
{
    this->artist = artist;
}
void Song::setFile(const QByteArray &value)
{
    file = value;
}

